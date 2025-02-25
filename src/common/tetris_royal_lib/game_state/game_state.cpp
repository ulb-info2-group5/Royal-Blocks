#include "game_state.hpp"
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
        if (playerStateTetris.pPlayerState_->isAlive()) {
            if (winner.has_value()) {
                // had already found a player that is
                // still alive -> more than one player
                // alive -> no winner yet.
                return std::nullopt;
            }

            winner = playerStateTetris.pPlayerState_->getPlayerID();
        }
    }

    return winner;
}

PlayerStatePtr GameState::getPlayerState(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState_->getPlayerID() == playerID) {
            return playerStateTetris.pPlayerState_;
        }
    }

    return nullptr;
}

TetrisPtr GameState::getTetris(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.pPlayerState_->getPlayerID() == playerID) {
            return playerStateTetris.pTetris_;
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
        if (playerTetris.pPlayerState_->getPlayerID() == playerID) {
            j["self"] = playerTetris.serializeSelf();
        } else {
            j["externals"].push_back(playerTetris.serializeExternal());
        }
    }

    return j;
}
