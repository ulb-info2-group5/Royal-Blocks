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

#include "tetris_self.hpp"

#include <map>
#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

#include "board/board.hpp"
#include "core/in_game/tetromino/tetromino.hpp"
#include "core/in_game/tetromino_queue/tetromino_queue.hpp"
#include "vec2/vec2.hpp"

void client::TetrisSelf::deserialize(const nlohmann::json &j) {
    if (!j.at("activeTetromino").is_null()) {
        activeTetromino = std::make_optional(Tetromino{});
        activeTetromino->deserialize(j.at("activeTetromino"));
    } else {
        activeTetromino = std::nullopt;
    }

    if (!j.at("previewTetromino").is_null()) {
        previewTetromino = std::make_optional(Tetromino{});
        previewTetromino->deserialize(j.at("previewTetromino"));
    } else {
        previewTetromino = std::nullopt;
    }

    board.deserialize(j.at("board"));

    if (!j.at("holdTetromino").is_null()) {
        holdTetromino = std::make_optional(Tetromino{});
        holdTetromino->deserialize(j.at("holdTetromino"));
    } else {
        holdTetromino = std::nullopt;
    }

    tetrominoQueue.deserialize(j.at("tetrominoQueue"));
};
