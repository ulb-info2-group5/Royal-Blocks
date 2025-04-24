#ifndef GAME_STATE_CLIENT_HPP
#define GAME_STATE_CLIENT_HPP

#include "../../../client/core/in_game/game_state/game_state.hpp"

#include "../../../client/core/in_game/game_state/game_state_viewer.hpp"

#include "../binding_type.hpp"
#include "../bindings/constants.hpp"

#include <nlohmann/json.hpp>

/**
 * This file contains everything related to deserialization of GameState (used
 * by the client).
 */

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Namespace for all the serialization/deserialization of GameState
     * binding.
     */
    namespace GameStateMessage {

        /**
         * @brief Deserializes the given GameState binding into a
         * client::GameState.
         */
        client::GameState deserializeForPlayer(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::GameState) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            client::GameState gameStateBinding;
            gameStateBinding.deserialize(data.at("gameState"));
            return gameStateBinding;
        };

        /**
         * @brief Deserializes the given GameState binding into a
         * client::GameStateViewer.
         */
        client::GameStateViewer deserializeForViewer(const nlohmann::json &j) {
            if (j.at(PACKET_TYPE_FIELD) != BindingType::GameStateViewer) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            client::GameStateViewer gameStateViewerBinding;
            gameStateViewerBinding.deserialize(data.at("gameState"));

            return gameStateViewerBinding;
        };

    } // namespace GameStateMessage

} // namespace bindings

#endif // BINDING_GAME_STATE_CLIENT_HPP
