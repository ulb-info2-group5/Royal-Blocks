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
