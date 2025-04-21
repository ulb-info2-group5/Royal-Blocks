#ifndef BINDINGS_USER_STATE_HPP
#define BINDINGS_USER_STATE_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "binding_type.hpp"

#include <cstddef>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

using PlayerID = size_t;

/**
 * For an overview of the bindings system and the list of available binding, see
 * bindings_type.hpp.
 */
namespace bindings {

    /**
     * @brief Binding representing a user's state.
     */
    enum class State {
        Offline,
        Menu,
        Matchmaking,
        InGame,
        Viewer,
    };

}; // namespace bindings

#endif
