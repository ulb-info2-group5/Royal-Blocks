#include "grid_cell.hpp"
#include <optional>
#include <stdexcept>

bool GridCell::isEmpty() const noexcept { return !(colorId_.has_value()); }

unsigned GridCell::getColorId() const {
    if (isEmpty()) {
        throw std::runtime_error("Cell is empty, no color index");
    }

    return colorId_.value();
}

void GridCell::setColorId(unsigned colorIndex) noexcept {
    colorId_ = colorIndex;
}

void GridCell::setEmpty() noexcept { colorId_.reset(); };
