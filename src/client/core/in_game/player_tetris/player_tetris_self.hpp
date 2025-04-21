#ifndef CLIENT_PLAYER_TETRIS_SELF_HPP
#define CLIENT_PLAYER_TETRIS_SELF_HPP

#include "../player_state/player_state_self.hpp"
#include "../tetris/tetris_self.hpp"
#include "abstract_player_tetris.hpp"

namespace client {

    /**
     * @brief Self player tetris. "Self" means that this packet contains all the
     * information about that player and its associated Tetris, it is supposed
     * to be sent only to the player themself.
     */
    struct PlayerTetrisSelf final : public AbstractPlayerTetris {
        PlayerStateSelf playerState;
        TetrisSelf tetris;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_SELF_HPP
