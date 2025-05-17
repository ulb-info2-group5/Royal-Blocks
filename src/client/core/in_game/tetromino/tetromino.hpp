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

#ifndef CLIENT_TETROMINO_HPP
#define CLIENT_TETROMINO_HPP

#include "../../../../common/tetris_lib/vec2/vec2.hpp"

#include <nlohmann/json_fwd.hpp>
#include <vector>

namespace client {

    /**
     * @brief Tetromino struct.
     */
    struct Tetromino {
        Vec2 anchorPoint;
        std::vector<Vec2> body;
        unsigned colorId;

        /**
         * @brief Deserializes the tetromino.
         */
        void deserialize(const nlohmann::json &j);
    };

} // namespace client

#endif // CLIENT_TETROMINO_HPP
