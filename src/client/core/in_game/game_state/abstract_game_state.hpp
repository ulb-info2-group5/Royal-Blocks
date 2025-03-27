#ifndef CLIENT_ABSTRACT_GAME_STATE_HPP
#define CLIENT_ABSTRACT_GAME_STATE_HPP

#include "../player_tetris/player_tetris_external.hpp"

#include "../../../../common/tetris_royal_lib/effect/effect_type.hpp"
#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"

namespace client {

    struct AbstractGameState {
        bool isFinished = true; // default to not in a game
        GameMode gameMode;
        std::vector<PlayerTetrisExternal> externals;
        std::vector<std::pair<EffectType, Energy>> effectsPrice;

        AbstractGameState() = default;

        virtual ~AbstractGameState() = default;

        virtual void deserialize(const nlohmann::json &j) = 0;
    };

} // namespace client

#endif // CLIENT_ABSTRACT_GAME_STATE_HPP
