#ifndef CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
#define CLIENT_PLAYER_TETRIS_EXTERNAL_HPP

#include "../player_state/player_state_external.hpp"
#include "../tetris/tetris_external.hpp"

namespace client {

    struct PlayerTetrisExternal {
        PlayerStateExternal playerState_;
        TetrisExternal tetris_;

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
