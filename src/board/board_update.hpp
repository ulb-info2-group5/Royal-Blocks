#ifndef BOARD_UPDATE_HPP
#define BOARD_UPDATE_HPP

#include <cstddef>

class BoardUpdate {
  private:
    size_t numDestroyedRows = 0;
    size_t numDestroyedCols = 0;

  public:
    size_t getNumDestroyedRows();
    size_t getNumDestroyedColumns();

    void incrementDestroyedRows();
    void incrementDestroyedCols();
};

#endif
