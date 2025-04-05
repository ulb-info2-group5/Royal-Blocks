#include "game_engine.hpp"
#include "../effect/bonus/slow_down.hpp"
#include "../game_mode/game_mode.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "effect/penalty/penalty_type.hpp"
#include "effect/penalty/timed_penalty.hpp"
#include "effect_price/effect_price.hpp"
#include "player_state/player_state.hpp"
#include "player_tetris/player_tetris.hpp"
#include "tetris/tetris.hpp"
#include "tetromino/tetromino.hpp"
#include "tetromino/tetromino_shapes.hpp"

#include <cassert>
#include <optional>
#include <stdexcept>
#include <variant>

/* ------------------------------------------------
 *          Private Methods
 * ------------------------------------------------*/

bool GameEngine::checkFeatureEnabled(GameModeFeature gameModeFeature) const {
    return GameEngine::checkFeatureEnabled(pGameState_->getGameMode(),
                                           gameModeFeature);
}

void GameEngine::handlePlayerTimedEffect(PlayerTetris &playerTetris) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    TimedBonusPtr &pActiveBonus = playerTetris.pPlayerState->getActiveBonus();
    if (pActiveBonus != nullptr) {
        // currently has an active bonus
        pActiveBonus->tick();
        if (playerTetris.pPlayerState->getActiveBonus()->isFinished()) {
            playerTetris.pPlayerState->getActiveBonus().reset();
        }
    } else {
        // currently has no active bonus
        playerTetris.pPlayerState->fetchGrantedBonus().transform(
            [&playerTetris, this](BonusType bonusType) {
                if (bonusType == BonusType::MiniTetrominoes) {
                    handleMiniTetrominoes(*playerTetris.pTetris);
                } else {
                    playerTetris.pPlayerState->setActiveBonus(
                        TimedBonus::makeBonus(bonusType));
                }

                return 0;
            });
    }

    TimedPenaltyPtr &pActivePenalty =
        playerTetris.pPlayerState->getActivePenalty();
    if (pActivePenalty != nullptr) {
        // currently has an active penalty
        pActivePenalty->tick();
        if (playerTetris.pPlayerState->getActivePenalty()->isFinished()) {
            playerTetris.pPlayerState->getActivePenalty().reset();
        }
    } else {
        // currently has no active penalty
        playerTetris.pPlayerState->fetchReceivedPenalty().transform(
            [&playerTetris, this](PenaltyType penaltyType) {
                if (penaltyType == PenaltyType::Lightning) {
                    handleLightning(*playerTetris.pTetris);
                } else {
                    playerTetris.pPlayerState->setActivePenalty(
                        TimedPenalty::makePenalty(penaltyType));
                }

                return 0;
            });
    }
}

bool GameEngine::shouldReverseControls(PlayerState &playerState) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    const TimedPenaltyPtr &pPenalty = playerState.getActivePenalty();
    if (pPenalty == nullptr) {
        return false;
    }

    return pPenalty->getPenaltyType() == PenaltyType::ReverseControls;
}

bool GameEngine::shouldLockInput(PlayerState &playerState) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedPenaltyPtr &pPenalty = playerState.getActivePenalty();
    if (pPenalty == nullptr) {
        return false;
    }

    return pPenalty->getPenaltyType() == PenaltyType::InputLock;
}

TetrominoMove
GameEngine::invertTetrominoMove(TetrominoMove tetrominoMove) const {
    switch (tetrominoMove) {
    case TetrominoMove::Left:
        return TetrominoMove::Right;
        break;
    case TetrominoMove::Right:
        return TetrominoMove::Left;
        break;
    default:
        return tetrominoMove;
    }
}

bool GameEngine::shouldIgnoreTick(PlayerState &playerState) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedBonusPtr &pActiveBonus = playerState.getActiveBonus();
    if (pActiveBonus == nullptr) {
        return false;
    }

    if (pActiveBonus->getBonusType() != BonusType::SlowDown) {
        return false;
    }

    std::shared_ptr<SlowDown> pSlowDownBonus =
        std::dynamic_pointer_cast<SlowDown>(pActiveBonus);
    if (pSlowDownBonus == nullptr) {
        return false;
    }

    return pSlowDownBonus->shouldIgnoreTick();
}

void GameEngine::sendPenaltyEffect(const PlayerState &playerStateSender,
                                   PenaltyType penaltyType) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    std::optional<UserID> target = playerStateSender.getPenaltyTarget();

    if (!target.has_value()) {
        throw std::runtime_error{"sendPenaltyEffect: Player attempted to "
                                 "send penalty effect but "
                                 "has no target selected."};
    }

    PlayerStatePtr pPlayerStateTarget =
        pGameState_->getPlayerState(target.value());
    if (pPlayerStateTarget == nullptr) {
        throw std::runtime_error{
            "sendPenaltyEffect: Penalty target not found."};
    }

    pPlayerStateTarget->receivePenalty(penaltyType);
}

void GameEngine::sendPenaltyRows(const PlayerState &playerStateSender,
                                 size_t numRows) {
    if (!checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        return;
    }

    std::optional<UserID> targetID = playerStateSender.getPenaltyTarget();

    if (!targetID.has_value()) {
        throw std::runtime_error{
            "sendPenaltyRows: A player attempted to send penalty rows but "
            "has no target selected."};
    }

    TetrisPtr pTetrisTarget = pGameState_->getTetris(targetID.value());
    if (pTetrisTarget == nullptr) {
        throw std::runtime_error{
            "sendPenaltyRows: Penalty target's tetris not found."};
    }

    pTetrisTarget->eventReceivePenaltyRows(numRows);
}

bool GameEngine::checkCanBuyEffect(const PlayerState &playerState,
                                   EffectType effectType) const {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    return playerState.getEnergy() >= getEffectPrice(effectType);
}

void GameEngine::handleMiniTetrominoes(Tetris &tetris) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    constexpr int NUM_MINI_TETROMINOS = 2;

    // Push 2 MiniTetrominoes at the front of the player's queue.
    for (int i = 0; i < NUM_MINI_TETROMINOS; i++) {
        tetris.insertNextTetromino(
            Tetris::createTetromino(TetrominoShape::MiniTetromino));
    }
}

void GameEngine::handleLightning(Tetris &tetris) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    tetris.destroy2By2Occupied();
}

Score GameEngine::calculatePointsClearedRows(size_t numClearedRows) const {
    // TODO: Adapt this to what the assistant asked
    return numClearedRows * 100;
}

Energy GameEngine::calculateEnergyClearedRows(size_t numClearedRows) const {
    // TODO: Adapt this to what the assistant asked
    return numClearedRows;
}

bool GameEngine::checkAlive(const PlayerStatePtr &pPlayerState) const {
    if (pPlayerState == nullptr) {
        return false;
    }

    return pPlayerState->isAlive();
}

void GameEngine::tick(PlayerTetris &playerTetris) {
    playerTetris.pPlayerState->notifyEngineTick();

    if (!playerTetris.pPlayerState->isGameTick()) {
        return;
    }

    if (checkFeatureEnabled(GameEngine::GameModeFeature::Effects)) {
        // ignore tick (slowdown bonus)
        if (shouldIgnoreTick(*playerTetris.pPlayerState)) {
            return;
        }
    }

    const TetrisPtr &pTetris = playerTetris.pTetris;
    const PlayerStatePtr &pPlayerState = playerTetris.pPlayerState;

    size_t numClearedRows = pTetris->eventClockTick();
    Score earnedPoints = calculatePointsClearedRows(numClearedRows);
    pPlayerState->increaseScore(earnedPoints);

    // TODO: remove code duplication with bigDrop
    if (checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        pPlayerState->getPenaltyTarget().transform([&](UserID targetID) {
            if (checkAlive(targetID) && numClearedRows >= 2) {
                // For n (>= 2) rows cleared by the player, his target
                // receives n-1 penalty rows.
                sendPenaltyRows(*pPlayerState, numClearedRows - 1);
            }

            return 0;
        });
    }

    if (checkFeatureEnabled(GameModeFeature::Effects)) {
        Energy earnedEnergy = calculateEnergyClearedRows(numClearedRows);
        pPlayerState->increaseEnergy(earnedEnergy);
    }
}

/* ------------------------------------------------
 *          Public Methods
 * ------------------------------------------------*/

GameEngine::GameEngine(const GameStatePtr &pGameState)
    : pGameState_(pGameState) {}

void GameEngine::tryBuyEffect(UserID buyerID, EffectType effectType,
                              bool stashForLater) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    PlayerStatePtr pPlayerStateBuyer = pGameState_->getPlayerState(buyerID);
    if (!checkAlive(pPlayerStateBuyer)) {
        return;
    }

    // Not enough energy to buy the effect
    if (!checkCanBuyEffect(*pPlayerStateBuyer, effectType)) {
        return;
    }

    // Stash if penalty and no target defined/dead
    std::optional<UserID> optTargetID = pPlayerStateBuyer->getPenaltyTarget();
    bool targetAlive = optTargetID.has_value() && checkAlive(*optTargetID);
    if (std::holds_alternative<PenaltyType>(effectType) && !targetAlive) {
        stashForLater = true;
    }

    // Cannot stash bonuses
    if (stashForLater && std::holds_alternative<BonusType>(effectType)) {
        return;
    }

    std::visit(
        [&](auto &&effectType) {
            using T = std::decay_t<decltype(effectType)>;
            if constexpr (std::is_same_v<T, BonusType>) {
                // Bonus case
                pPlayerStateBuyer->grantBonus(effectType);
            } else if constexpr (std::is_same_v<T, PenaltyType>) {
                // Penalty case
                if (stashForLater) {
                    pPlayerStateBuyer->stashPenalty(effectType);
                } else {
                    sendPenaltyEffect(*pPlayerStateBuyer, effectType);
                }
            }
        },
        effectType);

    pPlayerStateBuyer->decreaseEnergy(getEffectPrice(effectType));
}

void GameEngine::selectTarget(UserID userID, UserID target) {
    if (!checkFeatureEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    // Ensure that both players are alive and exist
    PlayerStatePtr pPlayerStatePlayer = pGameState_->getPlayerState(userID);
    PlayerStatePtr pPlayerStateTarget = pGameState_->getPlayerState(target);
    if (!(checkAlive(pPlayerStatePlayer) && checkAlive(pPlayerStateTarget))) {
        return;
    }

    pPlayerStatePlayer->setPenaltyTarget(target);
}

void GameEngine::tryMoveActive(UserID userID, TetrominoMove tetrominoMove) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!checkAlive(pPlayerState)) {
        return;
    }

    if (shouldLockInput(*pPlayerState)) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(userID);
    if (pTetris == nullptr) {
        return;
    }

    pTetris->eventTryMoveActive(shouldReverseControls(*pPlayerState)
                                    ? invertTetrominoMove(tetrominoMove)
                                    : tetrominoMove);
}

void GameEngine::bigDrop(UserID userID) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!checkAlive(pPlayerState)) {
        return;
    }

    if (shouldLockInput(*pPlayerState)) {
        return;
    }

    size_t numClearedRows = pGameState_->getTetris(userID)->eventBigDrop();
    Score earnedPoints = calculatePointsClearedRows(numClearedRows);
    pPlayerState->increaseScore(earnedPoints);

    // TODO: remove code duplication with tick
    if (checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        pPlayerState->getPenaltyTarget().transform([&](UserID targetID) {
            if (checkAlive(targetID) && numClearedRows >= 2) {
                // For n (>= 2) rows cleared by the player, his target
                // receives n-1 penalty rows.
                sendPenaltyRows(*pPlayerState, numClearedRows - 1);
            }

            return 0;
        });
    }

    if (checkFeatureEnabled(GameModeFeature::Effects)) {
        Energy earnedEnergy = calculateEnergyClearedRows(numClearedRows);
        pPlayerState->increaseEnergy(earnedEnergy);
    }
}

void GameEngine::holdNextTetromino(UserID userID) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!checkAlive(pPlayerState)) {
        return;
    }

    if (shouldLockInput(*pPlayerState)) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(userID);
    if (pTetris == nullptr) {
        return;
    }

    pTetris->eventHoldNextTetromino();
}

void GameEngine::tryRotateActive(UserID userID, bool rotateClockwise) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!checkAlive(pPlayerState)) {
        return;
    }

    if (shouldLockInput(*pPlayerState)) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(userID);
    if (pTetris == nullptr) {
        return;
    }

    pTetris->eventTryRotateActive(shouldReverseControls(*pPlayerState)
                                      ? !rotateClockwise
                                      : rotateClockwise);
}

void GameEngine::emptyPenaltyStash(UserID userID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!checkAlive(pPlayerState)) {
        return;
    }

    // Cannot empty the stash if the player has not target defined
    // or the target is dead.
    if (!(pPlayerState->getPenaltyTarget().has_value()
          && checkAlive(*pPlayerState->getPenaltyTarget()))) {
        return;
    }

    std::deque<PenaltyType> penaltiesQueue =
        pPlayerState->getStashedPenalties();

    while (!penaltiesQueue.empty()) {
        PenaltyType penaltyType = penaltiesQueue.front();
        sendPenaltyEffect(*pPlayerState, penaltyType);
        penaltiesQueue.pop_front();
    }
}

bool GameEngine::checkFeatureEnabled(GameMode gameMode,
                                     GameModeFeature gameModeFeature) {
    return featuresBitsets.at(static_cast<size_t>(gameMode))
        .test(static_cast<size_t>(gameModeFeature));
}

void GameEngine::tick() {
    auto alivePlayers = pGameState_->getPlayerToTetris()
                        | std::views::filter([](const auto &pt) {
                              return pt.pPlayerState->isAlive();
                          });

    for (auto &playerTetris : alivePlayers) {
        handlePlayerTimedEffect(playerTetris);

        tick(playerTetris);
    }
}

bool GameEngine::checkAlive(UserID userID) const {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    return checkAlive(pPlayerState);
}

std::optional<UserID> GameEngine::getWinner() const {
    if (pGameState_->getGameMode() == GameMode::Endless) {
        return std::nullopt;
    }

    auto alivePlayers = pGameState_->getPlayerToTetris()
                        | std::views::filter([](const auto &pt) {
                              return pt.pPlayerState->isAlive();
                          });

    assert(std::ranges::distance(alivePlayers) >= 1);

    if (std::ranges::distance(alivePlayers) > 1) {
        return std::nullopt;
    }

    return alivePlayers.begin()->pPlayerState->getUserID();
}

bool GameEngine::gameIsFinished() const {
    if (pGameState_->getGameMode() == GameMode::Endless) {
        // Return whether the single player is alive
        return !pGameState_->getPlayerToTetris().at(0).pPlayerState->isAlive();
    } else {
        return getWinner() != std::nullopt;
    }
}

void GameEngine::quitGame(UserID userID) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(userID);
    if (!pPlayerState) {
        return;
    }
    pPlayerState->setAlive(false);
}
