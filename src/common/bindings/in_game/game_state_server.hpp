#ifndef BINDINGS_GAME_STATE_SERVER_HPP
#define BINDINGS_GAME_STATE_SERVER_HPP

#include "../../tetris_royal_lib/game_state/game_state.hpp"

#include "../binding_type.hpp"
#include "player_state/player_state.hpp"

#include <nlohmann/json.hpp>

namespace bindings {

    namespace GameStateMessage {
        /**
         * TODO
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
