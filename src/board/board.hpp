#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/tetromino.hpp"
#include "board_update.hpp"
#include "grid_cell.hpp"
#include <array>
#include <cstddef>

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
     * @brief Returns a reference to the GridCell instance at the (x, y)
     * position in the grid.
     *
     * @param xCoord The y coordinate.
     * @param yCoord The x coordinate.
     *
     * @return A reference to the corresponding Gridcell in the
     * board.
     */
    virtual GridCell &at(size_t xCoord, size_t yCoord);

    /**
     * @brief Returns a reference to the row at the given vertical coordinate in
     * the grid.
     *
     * @param y The row's y coordinate.
     *
     * @return A reference to the Array of GridCells corresponding to the row.
     */
    virtual std::array<GridCell, width_> &getRow(size_t yCoord);

    /**
     * @brief Returns a const reference to the row at the given vertical
     * coordinate in the grid.
     *
     * @param y The row's y coordinate.
     *
     * @return A const reference to the Array of GridCells corresponding to the
     * row.
     */
    virtual const std::array<GridCell, width_> &getRow(size_t yCoord) const;

    /**
     * @brief Moves all rows above the specified row down by one position.
     * Used to fill gaps after clearing a specific row.
     *
     * @param yCoord The y-coordinate of the row above which all rows are
     * shifted down.
     */
    virtual void dropRowsAbove(size_t yCoord);

    /**
     * @brief Checks whether the row at the given y-coordinate is full.
     *
     * @param yCoord The row's y-coordinate.
     *
     * @return True if the row is full, meaning it has no empty GridCell;
     * otherwise, false.
     */
    virtual bool checkFullRow(size_t yCoord) const;

    /**
     * @brief Checks whether the column at the given x-coordinate is full.
     *
     * @param xCoord The column's x-coordinate.
     *
     * @return True if the col is full, meaning it has no empty GridCell;
     * otherwise, false.
     */
    virtual bool checkFullCol(size_t xCoord) const;

    /**
     * @brief Sets each cell on the row at the given y-coordinate to empty
     * state.
     *
     * @param yCoord The row's y-coordinate.
     */
    virtual void emptyRow(size_t yCoord);

    // NOTE: this is not required, but could be something to toggle,
    // e.g. for an "easy" mode or a temporary Bonus.
    /**
     * @brief Sets each cell on the column at the given x-coordinate to empty
     * state.
     *
     * @param xCoord The column's x-coordinate.
     */
    virtual void emptyCol(size_t xCoord);

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
     * (yCoord, xCoord) in the grid.
     *
     * @param yCoord The row index.
     * @param xCoord The column index.
     *
     * @return A const reference to the Gridcell located at (yCoord, xCoord) in
     * the board.
     */
    const GridCell &get(size_t yCoord, size_t xCoord) const;

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
