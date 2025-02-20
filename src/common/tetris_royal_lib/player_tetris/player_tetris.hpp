#ifndef PLAYER_TETRIS_HPP
#define PLAYER_TETRIS_HPP

#include "player_state/player_state.hpp"
#include "tetris/tetris.hpp"

struct PlayerTetris {
    PlayerState playerState_;
    Tetris tetris_;

    PlayerTetris(const PlayerState &playerState, Tetris tetris)
        : playerState_{playerState}, tetris_{std::move(tetris)} {}

    nlohmann::json serializeSelf() const;

    nlohmann::json serializeExternal() const;
};

#endif // PLAYER_TETRIS_HPP
