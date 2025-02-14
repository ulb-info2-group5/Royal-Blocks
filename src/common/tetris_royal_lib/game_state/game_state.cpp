#include "game_state.hpp"
#include "game_state_view.hpp"

#include <algorithm>
#include <optional>

GameState::GameState(GameMode gameMode) : gameMode_{gameMode} {}

/* ---------------------------------------------------------
 *                  GameStateView Interface
 * ---------------------------------------------------------*/

const std::vector<PlayerStateTetris> &GameState::getPlayerToTetris() const {
    return playerToTetris_;
}

const PlayerState *GameState::getPlayerState(PlayerID playerID) const {
    for (const PlayerStateTetris &playerStateTetris : getPlayerToTetris()) {
        if (playerStateTetris.first.getPlayerID() == playerID) {
            return &playerStateTetris.first;
        }
    }

    return nullptr;
}

const Tetris *GameState::getTetris(PlayerID playerID) const {
    for (const PlayerStateTetris &playerStateTetris : getPlayerToTetris()) {
        if (playerStateTetris.first.getPlayerID() == playerID) {
            return &playerStateTetris.second;
        }
    }

    return nullptr;
}

GameMode GameState::getGameMode() const { return gameMode_; }

std::optional<PlayerID> GameState::getWinner() const {
    std::optional<PlayerID> winner;

    for (const PlayerStateTetris &playerStateTetris : getPlayerToTetris()) {
        if (playerStateTetris.first.isAlive()) {
            if (winner.has_value()) {
                // had already found a player that is
                // still alive -> more than one player
                // alive -> no winner yet.
                return std::nullopt;
            }

            winner = playerStateTetris.first.getPlayerID();
        }
    }

    return winner;
}

/* ---------------------------------------------------------------
 *          Non-const Methods (not part of GameStateView)
 * ---------------------------------------------------------------*/

PlayerState *GameState::getPlayerState(PlayerID playerID) {
    return const_cast<PlayerState *>(GameStateView::getPlayerState(playerID));
}

Tetris *GameState::getTetris(PlayerID playerID) {
    return const_cast<Tetris *>(GameStateView::getTetris(playerID));
}

GameState::CircularIt GameState::getCircularItAt(size_t idx) {
    return CircularIt{playerToTetris_, idx};
}

GameState::CircularIt GameState::getCircularItEnd() {
    return getCircularItAt(playerToTetris_.size());
}

GameState::CircularIt GameState::getCircularIt(PlayerID playerID) {
    auto it = std::find_if(playerToTetris_.begin(), playerToTetris_.end(),
                           [playerID](const auto &element) {
                               return element.first.getPlayerID() == playerID;
                           });

    if (it != playerToTetris_.end()) {
        size_t playerIndex = std::distance(playerToTetris_.begin(), it);
        return getCircularItAt(playerIndex);
    }

    // Case no matching player is found -> expired iterator.
    return getCircularItEnd();
}
