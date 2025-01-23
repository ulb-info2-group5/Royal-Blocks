#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/tetromino.hpp"
#include "board_update.hpp"
#include "grid_cell.hpp"
#include <array>
#include <cstddef>
#include <memory>

class BoardTest;

/**
 * @class Board
 *
 * @brief Represents a Tetris game board with a width and height. The
 * board contains a grid of GridCell objects.
 *
 * @note The board interacts with Tetrominoes only to check if they fit and to
 * place them. It does not store Tetrominoes but updates its GridCell objects
 * based on the Tetromino's shape, position, and color.
 */
class Board final {
  private:
    static constexpr size_t width_ = 10;
    static constexpr size_t height_ = 20;
    std::array<std::array<GridCell, width_>, height_> grid_;

    // #### Internal helper ####

    /**
     * @brief Returns a reference to the GridCell instance at the (row, col)
     * position in the grid.
     *
     * @param rowIdx The row index.
     * @param colIdx The column index.
     *
     * @return A reference to the Gridcell located at (rowIdx, colIdx) in the
     * board.
     */
    virtual GridCell &at(size_t rowIdx, size_t colIdx);

    /**
     * @brief Returns a reference to the rowIdx-th row in the grid.
     *
     * @param rowIdx The row index.
     *
     * @return A reference to the Array of GridCells corresponding to the row.
     */
    virtual std::array<GridCell, width_> &getY(size_t rowIdx);

    /**
     * @brief Moves all rows above the specified row down by one position.
     * Used to fill gaps after clearing a specific row.
     *
     * @param rowIdx The index of the row above which all rows are shifted down.
     */
    virtual void dropRowsAbove(size_t rowIdx);

    /**
     * @brief Checks whether the rowIndex-th row is full.
     *
     * @param rowIdx The row index.
     *
     * @return True if the rowIdx-th row is full, meaning it has no empty
     * GridCell; otherwise, false.
     */
    virtual bool checkFullRow(size_t rowIdx) const;

    /**
     * @brief Checks whether the colIndex-th column is full.
     *
     * @param colIdx The column index.
     *
     * @return True if the colIdx-th col is full, meaning it has no empty
     * GridCell; otherwise, false.
     */
    virtual bool checkFullCol(size_t colIdx) const;

    /**
     * @brief Sets each cell on the rowIndex-th row to empty state.
     *
     * @param rowIdx The row index.
     */
    virtual void emptyRow(size_t rowIdx);

    // NOTE: this is not required, but could be something to toggle,
    // e.g. for an "easy" mode or a temporary Bonus.
    /**
     * @brief Sets each cell on the colIdx-th column to empty state.
     *
     * @param colIdx The column index.
     */
    virtual void emptyCol(size_t colIdx);

    // NOTE: this is not required, but could be something to toggle,
    // e.g. for an "easy" mode or a temporary Bonus.
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
     *
     * @param rowIdx The row index.
     * @param colIdx The column index.
     *
     * @return A const reference to the Gridcell located at (rowIdx, colIdx) in
     * the board.
     */
    const GridCell &get(size_t rowIdx, size_t colIdx) const;

    /**
     * @brief Returns the width of the grid.
     *
     * @return The width of the grid.
     */
    virtual size_t getWidth() const noexcept;

    /**
     * @brief Returns the height of the grid.
     *
     * @return The height of the grid.
     */
    virtual size_t getHeight() const noexcept;

    // #### Board Actions ####

    /**
     * @brief Places the given tetromino in the grid.
     *
     * @param tetromino A unique pointer to the tetromino to be placed.
     *
     * @note The Tetromino will no longer be accessible after this function gets
     * called, ensuring it cannot be moved after being placed in the grid.
     */
    virtual void placeTetromino(TetrominoPtr tetromino);

    /**
     * @brief Checks whether the specified Tetromino can fit in the grid given
     * its anchor-point and body.
     *
     * @param tetromino A reference to the Tetromino be checked.
     *
     * @return True if the given Tetromino fits; otherwise, false.
     */
    virtual bool checkInGrid(Tetromino &tetromino) const;

    // #### Update Board State ####

    /**
     * @brief Clears/Empties full rows, makes rows above the cleared row drop
     * one row down and returns a BoardUpdate object.
     *
     * @return A BoardUpdate object.
     */
    virtual BoardUpdate update();

    // #### Test Fixture Class ####

    friend BoardTest;
};

#endif
