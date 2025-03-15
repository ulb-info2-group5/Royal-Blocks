#ifndef CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
#define CLIENT_PLAYER_TETRIS_EXTERNAL_HPP

#include "../player_state/player_state_external.hpp"
#include "../tetris/tetris_external.hpp"
#include "abstract_player_tetris.hpp"

namespace client {

    struct PlayerTetrisExternal : public AbstractPlayerTetris {
        PlayerStateExternal playerState;
        TetrisExternal tetris;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
