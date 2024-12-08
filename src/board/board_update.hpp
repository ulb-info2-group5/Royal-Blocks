#ifndef BOARD_UPDATE_HPP
#define BOARD_UPDATE_HPP

#include <cstddef>

/**
 * @class BoardUpdate
 *
 * @brief Represents the result of a board update, including the number of rows
 * and columns cleared during the update.
 */
class BoardUpdate {
  private:
    size_t numClearedRows_;
    size_t numClearedCols_;

  public:
    /**
     * BoardUpdate constructor
     */
    BoardUpdate();

    /**
     * @brief Returns the number of rows cleared in this board update.
     *
     * @return Number of rows cleared in this board update.
     */
    size_t getNumClearedRows();

    /**
     * @brief Returns the number of columns cleared in this board update.
     *
     * @return Number of columns cleared in this board update.
     */
    size_t getNumClearedColumns();

    /**
     * @brief Increments the number of rows cleared in this board update.
     */
    void incrementClearedRows();

    /**
     * @brief Returns the number of columns cleared in this board update.
     */
    void incrementClearedCols();
};

#endif
