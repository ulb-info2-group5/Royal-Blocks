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

#ifndef CLIENT_ABSTRACT_GAME_STATE_HPP
#define CLIENT_ABSTRACT_GAME_STATE_HPP

#include "../player_tetris/player_tetris_external.hpp"

#include "../../../../common/tetris_royal_lib/effect/effect_type.hpp"
#include "../../../../common/tetris_royal_lib/game_mode/game_mode.hpp"

namespace client {

    /**
     * @brief Abtract class for client::GameState  and client::GameStateViewer.
     */
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
