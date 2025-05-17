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

#include "grid_cell.hpp"
#include <optional>

/*--------------------------------------------------
                    PUBLIC
--------------------------------------------------*/

GridCell::~GridCell() = default;

bool GridCell::isEmpty() const noexcept { return !(colorId_.has_value()); }

std::optional<unsigned> GridCell::getColorId() const { return colorId_; }

void GridCell::setColorId(unsigned colorIndex) noexcept {
    colorId_ = colorIndex;
}

void GridCell::setEmpty() noexcept { colorId_.reset(); };

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json GridCell::serialize() const {
    nlohmann::json j;
    if (colorId_) {
        j["colorId"] = *colorId_;
    } else {
        j["colorId"] = nullptr;
    }
    return j;
}

/**
 * @brief Deserializes the GridCell from json.
 */
void GridCell::deserialize(const nlohmann::json &j) {
    if (j.contains("colorId") && !j["colorId"].is_null()) {
        colorId_ = j.at("colorId").get<unsigned>();
    } else {
        colorId_ = std::nullopt;
    }
}
