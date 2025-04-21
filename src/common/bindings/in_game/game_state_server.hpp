#ifndef BINDINGS_GAME_STATE_SERVER_HPP
#define BINDINGS_GAME_STATE_SERVER_HPP

#include "../../tetris_royal_lib/game_state/game_state.hpp"

#include "../binding_type.hpp"
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
            return nlohmann::json{{"type", BindingType::GameState},
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
            return nlohmann::json{{"type", BindingType::GameStateViewer},
                                  {"data",
                                   {{
                                       "gameState",
                                       gameState.serializeForViewer(),
                                   }}}};
        };

    } // namespace GameStateMessage

} // namespace bindings

#endif // BINDINGS_GAME_STATE_SERVER_HPP
