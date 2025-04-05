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
