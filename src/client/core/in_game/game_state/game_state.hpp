#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "../player_tetris/player_tetris_self.hpp"
#include "abstract_game_state.hpp"

#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief Client GameState (player).
     */
    struct GameState : public AbstractGameState {
        PlayerTetrisSelf self;

        GameState() = default;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_GAME_STATE_HPP
