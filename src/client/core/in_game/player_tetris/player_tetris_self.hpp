#ifndef CLIENT_PLAYER_TETRIS_SELF_HPP
#define CLIENT_PLAYER_TETRIS_SELF_HPP

#include "../player_state/player_state_self.hpp"
#include "../tetris/tetris_self.hpp"
#include "abstract_player_tetris.hpp"

namespace client {

    struct PlayerTetrisSelf : public AbstractPlayerTetris {
        PlayerStateSelf playerState;
        TetrisSelf tetris;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_SELF_HPP
