#ifndef BINDINGS_USER_STATE_HPP
#define BINDINGS_USER_STATE_HPP

#include "../tetris_royal_lib/game_mode/game_mode.hpp"
#include "binding_type.hpp"

#include <cstddef>
#include <optional>
#include <string>

#include <nlohmann/json.hpp>

using PlayerID = size_t;

namespace bindings {
    enum class State {
        Offline,
        Menu,
        Matchmaking,
        InGame,
    };
};

#endif