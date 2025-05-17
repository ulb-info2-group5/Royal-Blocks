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

#ifndef CLIENT_PLAYER_TETRIS_SELF_HPP
#define CLIENT_PLAYER_TETRIS_SELF_HPP

#include "../player_state/player_state_self.hpp"
#include "../tetris/tetris_self.hpp"
#include "abstract_player_tetris.hpp"

#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief Self player tetris. "Self" means that this packet contains all the
     * information about that player and its associated Tetris, it is supposed
     * to be sent only to the player themself.
     */
    struct PlayerTetrisSelf final : public AbstractPlayerTetris {
        PlayerStateSelf playerState;
        TetrisSelf tetris;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_SELF_HPP
