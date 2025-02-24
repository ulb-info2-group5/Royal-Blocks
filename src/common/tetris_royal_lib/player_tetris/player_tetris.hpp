#ifndef PLAYER_TETRIS_HPP
#define PLAYER_TETRIS_HPP

#include "player_state/player_state.hpp"
#include "tetris/tetris.hpp"
#include <memory>

struct PlayerTetris {
    PlayerStatePtr pPlayerState_;
    TetrisPtr pTetris_;

    PlayerTetris(PlayerStatePtr &&pPlayerState)
        : pPlayerState_{pPlayerState}, pTetris_{std::make_shared<Tetris>()} {

        // Register the player state as an observer of the Tetris instance.
        // This allows the player state to be notified of game events such as
        // defeat.
        pTetris_->addObserver(pPlayerState_);
    }

    nlohmann::json serializeSelf() const;

    nlohmann::json serializeExternal() const;
};

#endif // PLAYER_TETRIS_HPP
