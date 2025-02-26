#include "game_engine.hpp"
#include "../effect/bonus/slow_down.hpp"
#include "../effect_price/effect_price.cpp"
#include "../game_mode/game_mode.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "effect/penalty/penalty_type.hpp"
#include "effect/penalty/timed_penalty.hpp"
#include "effect_price/effect_price.hpp"
#include "player_state/player_state.hpp"
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

void GameEngine::handlePlayerTimedEffect(PlayerState &playerState) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    if (playerState.getActiveBonus() != nullptr) {
        // currently has an active bonus
        if (playerState.getActiveBonus()->isFinished()) {
            playerState.getActiveBonus().reset();
        }
    } else {
        // currently has no active bonus
        playerState.fetchGrantedBonus().and_then(
            [&playerState](BonusType bonusType) {
                playerState.setActiveBonus(TimedBonus::makeBonus(bonusType));
                return std::optional<BonusType>{};
            });
    }

    if (playerState.getActivePenalty() != nullptr) {
        // currently has an active penalty
        if (playerState.getActivePenalty()->isFinished()) {
            playerState.getActivePenalty().reset();
        }
    } else {
        // currently has no active penalty
        playerState.fetchReceivedPenalty().and_then(
            [&playerState](PenaltyType penaltyType) {
                playerState.setActivePenalty(
                    TimedPenalty::makePenalty(penaltyType));
                return std::optional<PenaltyType>{};
            });
    }
}

void GameEngine::handleAllTimedEffects() {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    for (PlayerTetris &playerTetris : pGameState_->getPlayerToTetris()) {
        if (playerTetris.pPlayerState_->isAlive()) {
            handlePlayerTimedEffect(*playerTetris.pPlayerState_);
        }
    }
}

bool GameEngine::shouldReverseControls(const PlayerState &playerState) const {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedPenaltyPtr pPenalty = playerState.getActivePenalty();

    if (pPenalty == nullptr) {
        return false;
    }

    return pPenalty->getPenaltyType() == PenaltyType::ReverseControls;
}

bool GameEngine::shouldLockInput(const PlayerState &playerState) const {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedPenaltyPtr pPenalty = playerState.getActivePenalty();

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

bool GameEngine::shouldIgnoreTick(const PlayerState &playerState) const {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return false;
    }

    TimedBonusPtr pActiveBonus = playerState.getActiveBonus();

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

    // TODO: Decide whether a player can have no selected target at the
    // beginning of the game. If so, one more case to handle with the
    // optional (nullopt)

    std::optional<PlayerID> target = playerStateSender.getPenaltyTarget();

    if (!target.has_value()) {
        throw std::runtime_error{
            "sendPenaltyEffect: Player attempted to send penalty effect but "
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

    std::optional<PlayerID> targetID = playerStateSender.getPenaltyTarget();

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

    pTetrisTarget->eventReceivePenaltyLines(numRows);
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

/* ------------------------------------------------
 *          Public Methods
 * ------------------------------------------------*/

GameEngine::GameEngine(const GameStatePtr &pGameState)
    : pGameState_(pGameState) {}

void GameEngine::tryBuyEffect(PlayerID buyerID, EffectType effectType,
                              bool stashForLater) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    // Not enough energy to buy the effect
    if (!checkCanBuyEffect(buyerID, effectType)) {
        return;
    }

    // Cannot stash bonuses
    if (stashForLater && std::holds_alternative<BonusType>(effectType)) {
        return;
    }

    PlayerStatePtr pPlayerStateBuyer = pGameState_->getPlayerState(buyerID);
    if (pPlayerStateBuyer == nullptr) {
        return;
    }

    // The player must have either have a target defined or stash.
    if (!(pPlayerStateBuyer->getPenaltyTarget().has_value() || stashForLater)) {
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
                    sendPenaltyEffect(buyerID, effectType);
                }
            }
        },
        effectType);

    pPlayerStateBuyer->decreaseEnergy(getEffectPrice(effectType));
}

void GameEngine::selectTarget(PlayerID playerID, PlayerID target) {
    if (!checkFeatureEnabled(GameModeFeature::SelectPenaltyTarget)) {
        return;
    }

    PlayerStatePtr pPlayerStatePlayer = pGameState_->getPlayerState(playerID);
    PlayerStatePtr pPlayerStateTarget = pGameState_->getPlayerState(target);
    if (pPlayerStatePlayer == nullptr || pPlayerStateTarget == nullptr) {
        return;
    }

    // ensure that both players are alive
    if (!(pPlayerStatePlayer->isAlive() && pPlayerStateTarget->isAlive())) {
        return;
    }

    pPlayerStatePlayer->setPenaltyTarget(target);
}

void GameEngine::selectNextEffect(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    pPlayerState->selectNextEffect();
}

void GameEngine::selectPrevEffect(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    pPlayerState->selectPrevEffect();
}

void GameEngine::tryMoveActive(PlayerID playerID, TetrominoMove tetrominoMove) {
    if (shouldLockInput(playerID)) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(playerID);
    if (pTetris == nullptr) {
        return;
    }

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    pTetris->eventTryMoveActive(shouldReverseControls(*pPlayerState)
                                    ? invertTetrominoMove(tetrominoMove)
                                    : tetrominoMove);
}

void GameEngine::bigDrop(PlayerID playerID) {
    size_t numClearedRows = pGameState_->getTetris(playerID)->eventBigDrop();
    Score earnedPoints = calculatePointsClearedRows(numClearedRows);

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    pPlayerState->increaseScore(earnedPoints);
}

void GameEngine::holdNextTetromino(PlayerID playerID) {
    TetrisPtr pTetris = pGameState_->getTetris(playerID);
    if (pTetris == nullptr) {
        return;
    }

    pTetris->eventHoldNextTetromino();
}

void GameEngine::tryRotateActive(PlayerID playerID, bool rotateClockwise) {
    if (shouldLockInput(playerID)) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(playerID);
    if (pTetris == nullptr) {
        return;
    }

    pTetris->eventTryRotateActive(
        shouldReverseControls(playerID) ? !rotateClockwise : rotateClockwise);
}

void GameEngine::clockTick(PlayerID playerID) {
    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    TetrisPtr pTetris = pGameState_->getTetris(playerID);
    if (pTetris == nullptr) {
        throw std::runtime_error{
            "clockTick: player's tetris could not be found"};
    }

    TimedBonusPtr pActiveBonus = pPlayerState->getActiveBonus();

    handleAllTimedEffects();

    if (checkFeatureEnabled(GameEngine::GameModeFeature::Effects)) {
        if (pActiveBonus != nullptr) {
            pActiveBonus->tick();
        }

        // ignore tick (slowdown bonus)
        if (shouldIgnoreTick(playerID)) {
            return;
        }
    }

    size_t numClearedRows = pTetris->eventClockTick();

    Score earnedPoints = calculatePointsClearedRows(numClearedRows);

    pPlayerState->increaseScore(earnedPoints);

    if (checkFeatureEnabled(GameModeFeature::PenaltyRows)) {
        pPlayerState->getPenaltyTarget().and_then(
            [this, numClearedRows](PlayerID playerID) {
                // For n rows cleared by the player, his target receives n-1
                // penalty rows.
                sendPenaltyRows(playerID, numClearedRows - 1);
                return std::optional<PlayerID>{};
            });
    }

    if (checkFeatureEnabled(GameModeFeature::Effects)) {
        Energy earnedEnergy = calculateEnergyClearedRows(numClearedRows);
        pPlayerState->increaseEnergy(earnedEnergy);
    }
}

void GameEngine::emptyPenaltyStash(PlayerID playerID) {
    if (!checkFeatureEnabled(GameModeFeature::Effects)) {
        return;
    }

    PlayerStatePtr pPlayerState = pGameState_->getPlayerState(playerID);
    if (pPlayerState == nullptr) {
        return;
    }

    // Cannot empty the stash if the player has not target defined
    if (!pPlayerState->getPenaltyTarget().has_value()) {
        return;
    }

    std::deque<PenaltyType> penaltiesQueue =
        pPlayerState->getStashedPenalties();

    while (!penaltiesQueue.empty()) {
        PenaltyType penaltyType = penaltiesQueue.front();
        sendPenaltyEffect(playerID, penaltyType);
        penaltiesQueue.pop_front();
    }
}

bool GameEngine::checkFeatureEnabled(GameMode gameMode,
                                     GameModeFeature gameModeFeature) {
    return featuresBitsets.at(static_cast<size_t>(gameMode))
        .test(static_cast<size_t>(gameModeFeature));
}
