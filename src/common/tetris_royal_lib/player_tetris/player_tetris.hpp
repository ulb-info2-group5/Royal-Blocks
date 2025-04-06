#ifndef PLAYER_TETRIS_HPP
#define PLAYER_TETRIS_HPP

#include "player_state/player_state.hpp"
#include "tetris/tetris.hpp"

struct PlayerTetris {
    PlayerStatePtr pPlayerState;
    TetrisPtr pTetris;

    /**
     * @brief PlayerTetris Constructor
     */
    PlayerTetris(PlayerStatePtr &&pPlayerState);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the PlayerTetris to json without hiding information.
     */
    nlohmann::json serializeSelf() const;

    /**
     * @brief Serializes the PlayerTetris to json (hiding information as this
     * is meant to be used for players that aren't the player corresponding to
     * this PlayerTetris).
     */
    nlohmann::json serializeExternal() const;
};

#endif // PLAYER_TETRIS_HPP
