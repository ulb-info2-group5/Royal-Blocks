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

#include "tetromino.hpp"

#include <map>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>

#include "vec2/vec2.hpp"

void client::Tetromino::deserialize(const nlohmann::json &j) {
    anchorPoint.deserialize(j.at("anchorPoint"));
    colorId = j.at("colorId");

    body.clear();
    for (const auto &item : j.at("body")) {
        Vec2 v;
        v.deserialize(item);
        body.push_back(v);
    }
}
