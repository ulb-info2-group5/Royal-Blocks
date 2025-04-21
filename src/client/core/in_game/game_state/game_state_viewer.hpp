#ifndef CLIENT_GAME_STATE_VIEWER_HPP
#define CLIENT_GAME_STATE_VIEWER_HPP

#include "abstract_game_state.hpp"

namespace client {

    /**
     * @brief Client GameState (viewer).
     */
    struct GameStateViewer : public client::AbstractGameState {
        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_GAME_STATE_VIEWER_HPP
