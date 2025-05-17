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

#ifndef CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
#define CLIENT_PLAYER_TETRIS_EXTERNAL_HPP

#include "../player_state/player_state_external.hpp"
#include "../tetris/tetris_external.hpp"
#include "abstract_player_tetris.hpp"

#include <nlohmann/json_fwd.hpp>

namespace client {

    /**
     * @brief External player tetris. "External" means that some data is hidden
     * because only that player can see it.
     */
    struct PlayerTetrisExternal final : public AbstractPlayerTetris {
        PlayerStateExternal playerState;
        TetrisExternal tetris;

        void deserialize(const nlohmann::json &j) override;
    };

} // namespace client

#endif // CLIENT_PLAYER_TETRIS_EXTERNAL_HPP
