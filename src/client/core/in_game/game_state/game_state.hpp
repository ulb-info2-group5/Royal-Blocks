#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "../player_tetris/player_tetris_external.hpp"
#include "../player_tetris/player_tetris_self.hpp"

#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"

#include <vector>

namespace client {

    struct GameState {
        bool isFinished = true; // default to not in a game
        GameMode gameMode;
        PlayerTetrisSelf self;
        std::vector<PlayerTetrisExternal> externals;
        std::vector<std::pair<EffectType, Energy>> effectsPrice;

        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_GAME_STATE_HPP
