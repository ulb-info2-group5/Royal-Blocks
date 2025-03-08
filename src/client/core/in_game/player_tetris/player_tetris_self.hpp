#ifndef CLIENT_PLAYER_TETRIS_SELF_HPP
#define CLIENT_PLAYER_TETRIS_SELF_HPP

#include "../player_state/player_state_self.hpp"
#include "../tetris/tetris_self.hpp"

namespace client {

    struct PlayerTetrisSelf {
        PlayerStateSelf playerState_;
        TetrisSelf tetris_;

        nlohmann::json serialize() const;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_SELF_HPP
