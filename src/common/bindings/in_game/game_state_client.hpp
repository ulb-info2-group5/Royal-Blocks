/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

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
