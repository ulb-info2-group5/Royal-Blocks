#ifndef BOARD_UPDATE_HPP
#define BOARD_UPDATE_HPP

#include <cstddef>

/**
 * @class BoardUpdate
 *
 * @brief Represents the result of a board update, including the number of rows
 * and columns cleared during the update.
 */
class BoardUpdate final {
  private:
    size_t numClearedRows_;
    size_t numClearedCols_;

  public:
    /**
     * @brief BoardUpdate constructor
     */
    BoardUpdate();

    /**
     * @brief Returns the number of rows cleared in this board update.
     *
     * @return Number of rows cleared in this board update.
     */
    virtual size_t getNumClearedRows() const noexcept;

    /**
     * @brief Returns the number of columns cleared in this board update.
     *
     * @return Number of columns cleared in this board update.
     */
    virtual size_t getNumClearedColumns() const noexcept;

    /**
     * @brief Increments the number of rows cleared in this board update.
     */
    virtual void incrementClearedRows();

    /**
     * @brief Returns the number of columns cleared in this board update.
     */
    virtual void incrementClearedCols();
};

#endif
