#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/tetromino.hpp"
#include "grid_cell.hpp"
#include <array>
#include <cstddef>
#include <memory>

class Board {
  private:
    static constexpr size_t width_ = 10;
    static constexpr size_t height_ = 20;
    std::array<std::array<GridCell, width_>, height_> grid_;

  private:
    // #### Internal helper ####

    /**
     * @brief Returns a reference to the GridCell instance at the (row, col)
     * position in the grid.
     */
    virtual GridCell &at(size_t rowIdx, size_t colIdx);

    /**
     * @brief Returns a reference to the rowIdx-th row in the grid.
     */
    virtual std::array<GridCell, width_> &getRow(size_t rowIdx);

    /**
     * @brief Checks whether the rowIndex-th row is full.
     */
    virtual bool checkFullRow(size_t rowIdx) const;

    /**
     * @brief Checks whether the colIndex-th column is full.
     */
    virtual bool checkFullCol(size_t colIdx) const;

    /**
     * @brief Sets each cell on the rowIndex-th row to empty state.
     */
    virtual void emptyRow(size_t rowIdx);

    /**
     * @brief Sets each cell on the colIdx-th column to empty state.
     */
    virtual void emptyCol(size_t colIdx);

    /**
     * @brief Makes every non-empty cell drop down until it stands
     * either above another non-empty cell or at the bottom row of the
     * grid.
     */
    virtual void gravity();

  public:
    // #### Getters ####

    /**
     * @brief Returns a const reference to the GridCell instance at
     * (rowIdx, colIdx) in the grid.
     */
    const GridCell &get(size_t rowIdx, size_t colIdx) const;

    /**
     * @brief Returns the width of the grid.
     */
    size_t getWidth() const;

    /**
     * @brief Returns the height of the grid.
     */
    size_t getHeight() const;

    // #### Board Actions ####

    /**
     * @brief Places the given tetromino in the grid.
     *
     * @note The Tetromino will no longer be accessible after this function,
     * ensuring it cannot be moved after being placed in the grid.
     */
    virtual void placeTetromino(std::unique_ptr<Tetromino> tetromino);

    // #### Checks ####
    /**
     * @brief Checks whether the specified Tetromino can fit within the
     * current grid position.
     */
    bool checkInGrid(Tetromino &tetromino) const;

    /**
     * @brief Clears full rows and full columns and makes every levitating
     * non-empty cell drop down.
     */
    virtual void update();
};

#endif
