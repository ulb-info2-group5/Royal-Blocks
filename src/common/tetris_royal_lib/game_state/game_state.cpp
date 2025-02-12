#include "game_state.hpp"
#include "game_state_view.hpp"
#include <optional>

GameState::GameState(GameMode gameMode) : gameMode_{gameMode} {}

/* ---------------------------------------------------------
 *                  GameStateView Interface
 * ---------------------------------------------------------*/

const std::vector<PlayerStateTetris> &GameState::getPlayerToTetris() const {
    return playerToTetris_;
}

const PlayerState *GameState::getPlayerState(PlayerID playerID) const {
    for (const PlayerStateTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.first.getPlayerID() == playerID) {
            return &playerStateTetris.first;
        }
    }

    return nullptr;
}

const Tetris *GameState::getTetris(PlayerID playerID) const {
    for (const PlayerStateTetris &playerStateTetris : playerToTetris_) {
        if (playerStateTetris.first.getPlayerID() == playerID) {
            return &playerStateTetris.second;
        }
    }

    return nullptr;
}

GameMode GameState::getGameMode() const { return gameMode_; }

std::optional<PlayerID> GameState::getWinner() const {
    std::optional<PlayerID> winner;

    for (const PlayerStateTetris &playerStateTetris : playerToTetris_) {
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
