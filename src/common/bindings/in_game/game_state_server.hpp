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

#ifndef BINDINGS_GAME_STATE_SERVER_HPP
#define BINDINGS_GAME_STATE_SERVER_HPP

#include "../../tetris_royal_lib/game_state/game_state.hpp"

#include "../binding_type.hpp"
#include "../constants.hpp"
#include "player_state/player_state.hpp"

#include <nlohmann/json.hpp>

/**
 * This file contains everything related to serialization of GameState (used by
 * the server).
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
         * @brief Serializes the given gamestate for a player in the JSON
         * format.
         */
        nlohmann::json serializeForPlayer(const GameState &gameState,
                                          UserID userID) {
            return nlohmann::json{{PACKET_TYPE_FIELD, BindingType::GameState},
                                  {"data",
                                   {{
                                       "gameState",
                                       gameState.serializeForPlayer(userID),
                                   }}}};
        };

        /**
         * @brief Serializes the given gamestate for a viewer in the JSON
         * format.
         */
        nlohmann::json serializeForViewer(const GameState &gameState) {
            return nlohmann::json{
                {PACKET_TYPE_FIELD, BindingType::GameStateViewer},
                {"data",
                 {{
                     "gameState",
                     gameState.serializeForViewer(),
                 }}}};
        };

    } // namespace GameStateMessage

} // namespace bindings

#endif // BINDINGS_GAME_STATE_SERVER_HPP
