#ifndef GAME_STATE_CLIENT_HPP
#define GAME_STATE_CLIENT_HPP

#include "../../client/core/game_state/game_state.hpp"

#include "../binding_type.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    namespace GameStateMessage {
        /**
         * @brief Deserializes the given GameState binding into a
         * client::GameState.
         */
        client::GameState deserialize(const nlohmann::json &j) {
            if (j.at("type") != BindingType::GameState) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            client::GameState gameStateBinding;
            gameStateBinding.deserialize(data.at("gameState"));
            return gameStateBinding;
        };
    } // namespace GameStateMessage

} // namespace bindings

#endif // BINDING_GAME_STATE_CLIENT_HPP
