#ifndef PLAYER_TETRIS_HPP
#define PLAYER_TETRIS_HPP

#include "player_state/player_state.hpp"
#include "tetris/tetris.hpp"

struct PlayerTetris {
    PlayerState playerState_;
    Tetris tetris_;

    PlayerTetris(const PlayerState &playerState)
        : playerState_{playerState}, tetris_{} {

        // Register the player state as an observer of the Tetris instance.
        // This allows the player state to be notified of game events such as
        // defeat.
        tetris_.addObserver(&playerState_);
    }

    nlohmann::json serializeSelf() const;

    nlohmann::json serializeExternal() const;
};

#endif // PLAYER_TETRIS_HPP
