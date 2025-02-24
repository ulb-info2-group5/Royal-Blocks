#include "game_state.hpp"
#include "game_engine/game_engine.hpp"
#include "nlohmann/json_fwd.hpp"
#include "player_tetris/player_tetris.hpp"

#include <algorithm>
#include <optional>
#include <vector>

GameState::GameState(GameMode gameMode, std::vector<PlayerState> &&playerStates)
    : gameMode_{gameMode} {

    for (PlayerState &playerState : playerStates) {
        playerState.toggleEffects(GameEngine::checkFeatureEnabled(
            gameMode, GameEngine::GameModeFeature::Effects));
        playerToTetris_.emplace_back(PlayerTetris{playerState, Tetris{}});
    }
}

GameMode GameState::getGameMode() const { return gameMode_; }

std::optional<PlayerID> GameState::getWinner() const {
    std::optional<PlayerID> winner;

    for (const PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.playerState_.isAlive()) {
            if (winner.has_value()) {
                // had already found a player that is
                // still alive -> more than one player
                // alive -> no winner yet.
                return std::nullopt;
            }

            winner = playerStateTetris.playerState_.getPlayerID();
        }
    }

    return winner;
}

PlayerState *GameState::getPlayerState(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.playerState_.getPlayerID() == playerID) {
            return &playerStateTetris.playerState_;
        }
    }

    return nullptr;
}

Tetris *GameState::getTetris(PlayerID playerID) {
    for (PlayerTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.playerState_.getPlayerID() == playerID) {
            return &playerStateTetris.tetris_;
        }
    }

    return nullptr;
}

GameState::CircularIt GameState::getCircularItAt(size_t idx) {
    return CircularIt{playerToTetris_, idx};
}

GameState::CircularIt GameState::getCircularItEnd() {
    return getCircularItAt(playerToTetris_.size());
}

GameState::CircularIt GameState::getCircularIt(PlayerID playerID) {
    auto it =
        std::find_if(playerToTetris_.begin(), playerToTetris_.end(),
                     [playerID](const auto &element) {
                         return element.playerState_.getPlayerID() == playerID;
                     });

    if (it != playerToTetris_.end()) {
        size_t playerIndex = std::distance(playerToTetris_.begin(), it);
        return getCircularItAt(playerIndex);
    }

    // Case no matching player is found -> expired iterator.
    return getCircularItEnd();
}

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json GameState::serializeFor(PlayerID playerID) const {
    nlohmann::json j;

    j["gameMode"] = gameMode_;

    j["externals"] = nlohmann::json::array();

    for (const auto &playerTetris : playerToTetris_) {
        if (playerTetris.playerState_.getPlayerID() == playerID) {
            j["self"] = playerTetris.serializeSelf();
        } else {
            j["externals"].push_back(playerTetris.serializeExternal());
        }
    }

    return j;
}
