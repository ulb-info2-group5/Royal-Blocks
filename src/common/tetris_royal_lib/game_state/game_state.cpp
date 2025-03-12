#include "game_state.hpp"
#include "effect/bonus/bonus_type.hpp"
#include "game_engine/game_engine.hpp"
#include "nlohmann/json_fwd.hpp"
#include "player_tetris/player_tetris.hpp"

#include <memory>
#include <optional>
#include <vector>

GameState::GameState(GameMode gameMode, std::vector<PlayerState> &&playerStates)
    : gameMode_{gameMode} {

    for (PlayerState &playerState : playerStates) {
        playerState.toggleEffects(GameEngine::checkFeatureEnabled(
            gameMode, GameEngine::GameModeFeature::Effects));
        playerToTetris_.emplace_back(
            PlayerTetris{std::make_shared<PlayerState>(playerState)});
    }
}

GameMode GameState::getGameMode() const { return gameMode_; }

std::optional<PlayerID> GameState::getWinner() const {
    std::optional<PlayerID> winner;

    for (const PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->isAlive()) {
            if (winner.has_value()) {
                // had already found a player that is
                // still alive -> more than one player
                // alive -> no winner yet.
                return std::nullopt;
            }

            winner = playerStateTetris.pPlayerState->getPlayerID();
        }
    }

    return winner;
}

PlayerStatePtr GameState::getPlayerState(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->getPlayerID() == playerID) {
            return playerStateTetris.pPlayerState;
        }
    }

    return nullptr;
}

TetrisPtr GameState::getTetris(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState->getPlayerID() == playerID) {
            return playerStateTetris.pTetris;
        }
    }

    return nullptr;
}

std::vector<PlayerTetris> &GameState::getPlayerToTetris() {
    return playerToTetris_;
}

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json GameState::serializeFor(PlayerID playerID) const {
    nlohmann::json j;

    j["gameMode"] = gameMode_;

    j["externals"] = nlohmann::json::array();

    for (const auto &playerTetris : playerToTetris_) {
        if (playerTetris.pPlayerState->getPlayerID() == playerID) {
            j["self"] = playerTetris.serializeSelf();
        } else {
            j["externals"].push_back(playerTetris.serializeExternal());
        }
    }

    // add the effects that the players can buy with their price
    j["bonusToPrice"] = nlohmann::json::array();
    j["penaltyToPrice"] = nlohmann::json::array();
    if (GameEngine::checkFeatureEnabled(gameMode_,
                                        GameEngine::GameModeFeature::Effects)) {
        // bonuses
        for (size_t i = 0; i < static_cast<size_t>(BonusType::NumBonusType);
             i++) {
            BonusType bonusType = static_cast<BonusType>(i);
            j["bonusToPrice"].push_back({bonusType, getEffectPrice(bonusType)});
        }
        // penalties
        for (size_t i = 0; i < static_cast<size_t>(PenaltyType::NumPenaltyType);
             i++) {
            PenaltyType penaltyType = static_cast<PenaltyType>(i);
            j["penaltyToPrice"].push_back(
                {penaltyType, getEffectPrice(penaltyType)});
        }
    }

    return j;
}
