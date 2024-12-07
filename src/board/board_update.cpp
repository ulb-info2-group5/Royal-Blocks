#include "board_update.hpp"

#include <cstddef>

size_t BoardUpdate::getNumDestroyedRows() { return numDestroyedRows; }

size_t BoardUpdate::getNumDestroyedColumns() { return numDestroyedCols; }

void BoardUpdate::incrementDestroyedRows() { numDestroyedRows++; }

void BoardUpdate::incrementDestroyedCols() { numDestroyedCols++; }
