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

#ifndef CLIENT_GAME_STATE_HPP
#define CLIENT_GAME_STATE_HPP

#include "../player_tetris/player_tetris_self.hpp"
#include "abstract_game_state.hpp"

#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief Client GameState (player).
     */
    struct GameState : public AbstractGameState {
        PlayerTetrisSelf self;

        GameState() = default;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_GAME_STATE_HPP
