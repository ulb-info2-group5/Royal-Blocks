#include "board_update.hpp"

#include <cstddef>

BoardUpdate::BoardUpdate() : numClearedRows_{0}, numClearedCols_{0} {}

size_t BoardUpdate::getNumClearedRows() { return numClearedRows_; }

size_t BoardUpdate::getNumClearedColumns() { return numClearedCols_; }

void BoardUpdate::incrementClearedRows() { numClearedRows_++; }

void BoardUpdate::incrementClearedCols() { numClearedCols_++; }
