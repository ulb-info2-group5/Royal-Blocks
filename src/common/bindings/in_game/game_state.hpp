#ifndef BINDINGS_GAME_STATE_HPP
#define BINDINGS_GAME_STATE_HPP

#include "../../tetris_royal_lib/game_state/game_state.hpp"

#include "../../client/core/game_state/game_state.hpp"

#include "../binding_type.hpp"
#include "nlohmann/json_fwd.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    /**
     * @brief Wraps the given json that represents a GameState for a specific
     * player into an actual binding with "data" and "type" fields.
     */
    nlohmann::json to_json(const nlohmann::json &serializedGameState) {
        return nlohmann::json{{"type", BindingType::GameState},
                              {"data",
                               {{
                                   "gameState",
                                   serializedGameState,
                               }}}};
    };

    /**
     * @brief Deserializes the given GameState binding into a client::GameState.
     */
    client::GameState from_json(const nlohmann::json &j) {
        if (j.at("type") != BindingType::GameState) {
            throw std::runtime_error("Invalid type field in JSON");
        }

        const auto &data = j.at("data");
        client::GameState gameStateBinding;
        gameStateBinding.deserialize(data.at("gameState"));
        return gameStateBinding;
    };

} // namespace bindings

#endif // BINDINGS_GAME_STATE_HPP
