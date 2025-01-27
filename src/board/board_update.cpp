#include "board_update.hpp"

#include <cstddef>

/*--------------------------------------------------
                    PUBLIC
--------------------------------------------------*/

BoardUpdate::BoardUpdate() : numClearedRows_{0}, numClearedCols_{0} {}

BoardUpdate::~BoardUpdate() = default;

size_t BoardUpdate::getNumClearedRows() const noexcept {
    return numClearedRows_;
}

size_t BoardUpdate::getNumClearedColumns() const noexcept {
    return numClearedCols_;
}

void BoardUpdate::incrementClearedRows() { numClearedRows_++; }

void BoardUpdate::incrementClearedCols() { numClearedCols_++; }
