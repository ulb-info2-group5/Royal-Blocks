#include "grid_cell.hpp"
#include <stdexcept>

bool GridCell::isEmpty() const { return isEmpty_ == 0; }

unsigned GridCell::getColorId() const {
    if (isEmpty()) {
        throw std::runtime_error("Cell is empty, no color index");
    }

    return colorId_.value();
}

void GridCell::setColorId(unsigned colorIndex) {
    isEmpty_ = false;
    colorId_ = colorIndex;
}

void GridCell::setEmpty() {
    isEmpty_ = false;
    colorId_.reset();
};
