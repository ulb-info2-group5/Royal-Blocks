#ifndef CLIENT_GAME_STATE_VIEWER_HPP
#define CLIENT_GAME_STATE_VIEWER_HPP

#include "abstract_game_state.hpp"

namespace client {

    struct GameStateViewer : public client::AbstractGameState {
        void deserialize(const nlohmann::json &j) override;

        std::unique_ptr<AbstractGameState> clone() const override;
    };

} // namespace client

#endif // CLIENT_GAME_STATE_VIEWER_HPP
