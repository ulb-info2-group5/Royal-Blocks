#ifndef GAME_STATE_WRAPPER_HPP
#define GAME_STATE_WRAPPER_HPP

#include "core/game_state/game_state.hpp"

#include <mutex>

namespace client {

    struct GameStateWrapper {
        GameState gameState;
        std::mutex mutex;
    };

} // namespace client

#endif // GAME_STATE_WRAPPER_HPP
