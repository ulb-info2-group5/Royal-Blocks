#include "game_engine.hpp"
#include "../effect_price/effect_price.cpp"
#include "../game_mode/game_mode.hpp"
#include "effect/penalty/penalty_type.hpp"
#include "effect_price/effect_price.hpp"
#include "game_state/game_state.hpp"
#include "player_state/player_state.hpp"
#include "tetromino/tetromino.hpp"
#include "tetromino/tetromino_shapes.hpp"

#include <cassert>
#include <optional>
#include <stdexcept>
#include <variant>

bool GameEngine::checkFeatureEnabled(GameMode gameMode,
                                     GameModeFeature gameModeFeature) {
    return featuresBitsets.at(static_cast<size_t>(gameMode))
        .test(static_cast<size_t>(gameModeFeature));
}

bool GameEngine::checkFeatureEnabled(GameModeFeature gameModeFeature) const {
    return GameEngine::checkFeatureEnabled(pGameState_->getGameMode(),
                                           gameModeFeature);
}

bool GameEngine::shouldReverseControls(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedPenaltyPtr pPenalty =
        pGameState_->getPlayerState(playerID)->getActivePenalty();

    if (pPenalty == nullptr) {
        return false;
    }

    return pPenalty->getPenaltyType() == PenaltyType::ReverseControls;
}

bool GameEngine::shouldLockInput(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedPenaltyPtr pPenalty =
        pGameState_->getPlayerState(playerID)->getActivePenalty();

    if (pPenalty == nullptr) {
        return false;
    }

    return pPenalty->getPenaltyType() == PenaltyType::InputLock;
}

TetrominoMove GameEngine::invertTetrominoMove(TetrominoMove tetrominoMove) {
    switch (tetrominoMove) {
    case TetrominoMove::Left:
        return TetrominoMove::Right;
        break;
    case TetrominoMove::Right:
        return TetrominoMove::Left;
        break;
    default:
        throw std::runtime_error{"TetrominoMove::Down cannot be inverted"};
    }
}

GameEngine::GameEngine(const GameStatePtr &pGameState)
    : pGameState_(pGameState) {}

void GameEngine::sendPenaltyEffect(PlayerID senderID, PenaltyType penaltyType) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)
        || !checkFeatureEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    // TODO: Decide whether a player can have no selected target at the
    // beginning of the game. If so, one more case to handle with the
    // optional (nullopt)

    std::optional<PlayerID> target =
        pGameState_->getPlayerState(senderID)->getPenaltyTarget();

    pGameState_->getPlayerState(target.value())->receivePenalty(penaltyType);
}

void GameEngine::sendPenaltyRows(PlayerID senderID, size_t numRows) {
    if (checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        std::optional<PlayerID> targetID =
            pGameState_->getPlayerState(senderID)->getPenaltyTarget();

        if (!targetID.has_value()) {
            throw std::runtime_error{
                "A player attempted to send penalty rows but "
                "has no target selected."};
        } else {
            pGameState_->getTetris(targetID.value())
                ->eventReceivePenaltyLines(numRows);
        }
    }
}

bool GameEngine::checkCanBuyEffect(PlayerID buyerID, EffectType effectType) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    return pGameState_->getPlayerState(buyerID)->getEnergy()
           >= getEffectPrice(effectType);
}

void GameEngine::handleMiniTetrominoes(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    // Push 2 MiniTetrominoes at the front of the player's queue.
    for (int i = 0; i < 2; i++) {
        pGameState_->getTetris(playerID)->insertNextTetromino(
            Tetris::createTetromino(TetrominoShape::MiniTetromino));
    }
}

void GameEngine::handleLightning(PlayerID playerID) {
    pGameState_->getTetris(playerID)->destroy2By2Occupied();
}

void GameEngine::tryBuyEffect(PlayerID buyerID, EffectType effectType,
                              bool stashForLater) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    // Not enough energy to buy the effect
    if (!checkCanBuyEffect(buyerID, effectType)) {
        return;
    }

    // Take the player's energy (effect price)
    pGameState_->getPlayerState(buyerID)->decreaseEnergy(
        getEffectPrice(effectType));

    std::visit(
        [&](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, BonusType>) {
                // Bonus case
                pGameState_->getPlayerState(buyerID)->grantBonus(effectType);
            } else if constexpr (std::is_same_v<T, PenaltyType>) {
                // Penalty case
                if (stashForLater) {
                    pGameState_->getPlayerState(buyerID)->stashPenalty(
                        effectType);
                } else {
                    sendPenaltyEffect(buyerID, effectType);
                }
            }
        },
        effectType);
}

void GameEngine::selectTarget(PlayerID playerID, PlayerID target) {
    if (!checkFeatureEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->setPenaltyTarget(target);
}

Score GameEngine::calculatePointsClearedRows(size_t numClearedRows) {
    // TODO: Adapt this to what the assistant asked
    return numClearedRows * 100;
}

void GameEngine::selectNextAliveTarget(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    // Assume that if no target had been chosen by this player previously,
    // the target was the player himslef so that it chooses the player after
    // himself (in the getPlayerToTetris() vector) as next target.
    PlayerID prevTargetID =
        pGameState_->getPlayerState(playerID)->getPenaltyTarget().value_or(
            playerID);

    GameState::CircularIt playerSelfIt = pGameState_->getCircularIt(playerID);

    GameState::CircularIt prevTargetIt =
        pGameState_->getCircularIt(prevTargetID);

    GameState::CircularIt newTargetIt = prevTargetIt;

    do {
        ++newTargetIt;
        // TODO: Check that this is correct
        // avoid stopping the player himself
        if (newTargetIt == playerSelfIt) {
            ++newTargetIt;
        }
    } while (newTargetIt != prevTargetIt
             && !(*newTargetIt).playerState_.isAlive());

    // NOTE: This should never happen, if it does, the game should have
    // ended earlier because there is only one player left.
    assert(newTargetIt != playerSelfIt);

    PlayerID newTargetID = (*newTargetIt).playerState_.getPlayerID();

    pGameState_->getPlayerState(playerID)->setPenaltyTarget(newTargetID);
}

void GameEngine::selectNextEffect(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->selectNextEffect();
}

void GameEngine::selectPrevEffect(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    pGameState_->getPlayerState(playerID)->selectPrevEffect();
}

void GameEngine::tryMoveActive(PlayerID playerID, TetrominoMove tetrominoMove) {
    if (shouldLockInput(playerID)) {
        return;
    }

    pGameState_->getTetris(playerID)->eventTryMoveActive(
        shouldReverseControls(playerID) ? invertTetrominoMove(tetrominoMove)
                                        : tetrominoMove);
}

void GameEngine::bigDrop(PlayerID playerID) {
    pGameState_->getTetris(playerID)->eventBigDrop();
}

void GameEngine::holdNextTetromino(PlayerID playerID) {
    pGameState_->getTetris(playerID)->eventHoldNextTetromino();
}

void GameEngine::tryRotateActive(PlayerID playerID, bool rotateClockwise) {
    if (shouldLockInput(playerID)) {
        return;
    }

    pGameState_->getTetris(playerID)->eventTryRotateActive(
        shouldReverseControls(playerID) ? !rotateClockwise : rotateClockwise);
}

Energy GameEngine::calculateEnergyClearedRows(size_t numClearedRows) {
    // TODO: Adapt this to what the assistant asked
    return numClearedRows;
}

void GameEngine::clockTick(PlayerID playerID) {
    size_t numClearedRows = pGameState_->getTetris(playerID)->eventClockTick();

    Score earnedPoints = calculatePointsClearedRows(numClearedRows);

    pGameState_->getPlayerState(playerID)->increaseScore(earnedPoints);

    if (checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        // For n rows cleared by the player, his target receives n-1 penalty
        // rows.
        sendPenaltyRows(playerID, numClearedRows - 1);
    }

    if (checkFeatureEnabled(GameModeFeature::Effects)) {
        Energy earnedEnergy = calculateEnergyClearedRows(numClearedRows);
        pGameState_->getPlayerState(playerID)->increaseEnergy(earnedEnergy);
    }
}

void GameEngine::emptyPenaltyStash(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    std::deque<PenaltyType> penaltiesQueue =
        pGameState_->getPlayerState(playerID)->getStashedPenalties();

    while (!penaltiesQueue.empty()) {
        PenaltyType penaltyType = penaltiesQueue.front();
        sendPenaltyEffect(playerID, penaltyType);
        penaltiesQueue.pop_front();
    }
}
