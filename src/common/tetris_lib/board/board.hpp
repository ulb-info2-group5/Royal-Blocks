/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/abstract_tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "board_update.hpp"
#include "grid_cell.hpp"
#include <array>
#include <cstddef>

class BoardTest;

constexpr int PENALTY_BLOCKS_COLOR_ID =
    static_cast<int>(TetrominoShape::NumTetrominoShape);

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
class Board {
  private:
    static constexpr size_t width_ = 10;
    static constexpr size_t height_ = 20;
    std::array<std::array<GridCell, width_>, height_> grid_;

    // #### Internal helper ####

    /**
     * @brief Returns a reference to the GridCell instance at the (x, y)
     * position in the grid.
     *
     * @param xCol The x coordinate.
     * @param yRow The y coordinate.
     *
     * @return A reference to the corresponding Gridcell in the
     * board.
     */
    GridCell &at(int xCol, int yRow);

    /**
     * @brief Returns a reference to the row at the given vertical coordinate in
     * the grid.
     *
     * @param yRow The row's y coordinate.
     *
     * @return A reference to the Array of GridCells corresponding to the row.
     */
    std::array<GridCell, width_> &getRow(int yRow);

    /**
     * @brief Returns a const reference to the row at the given vertical
     * coordinate in the grid.
     *
     * @param yRow The row's y coordinate.
     *
     * @return A const reference to the Array of GridCells corresponding to the
     * row.
     */
    const std::array<GridCell, width_> &getRow(int yRow) const;

    /**
     * @brief Moves all rows above the specified row down by one position.
     * Used to fill gaps after clearing a specific row.
     *
     * @param yRow The y-coordinate of the row above which all rows are
     * shifted down.
     */
    void dropRowsAbove(int yRow);

    /**
     * @brief Moves all rows from the specified row up by a one position.
     *
     * This method ignores the fact that some tiles from the top row could go
     * out of the grid.
     *
     * @param yRow The y-coordinate of the row from which all rows are shifted
     * up.
     * @param numRows The number of rows to lift.
     */
    void liftRowsFrom(int yRow, size_t numRows);

    /**
     * @brief Sets row at yRow to the given row.
     *
     * @param row The new row.
     * @param yRow The y-coordinate of the row to set.
     */
    void setRow(const std::array<GridCell, width_> &row, size_t yRow);

    /**
     * @brief Replaces the given row by a penalty row.
     * Doesn't check whether the row was empty before doing so.
     *
     * @param row A reference to the row.
     */
    void setPenaltyRow(std::array<GridCell, width_> &row);

    /**
     * @brief Checks whether the row at the given y-coordinate is empty.
     *
     * @param yRow The row's y-coordinate.
     *
     * @return True if the row is empty, meaning it has only empty GridCells;
     * otherwise, false.
     */
    bool checkEmptyRow(int yRow) const;

    /**
     * @brief Checks whether the row at the given y-coordinate is full.
     *
     * @param yRow The row's y-coordinate.
     *
     * @return True if the row is full, meaning it has no empty GridCell;
     * otherwise, false.
     */
    bool checkFullRow(int yRow) const;

    /**
     * @brief Checks whether the column at the given x-coordinate is full.
     *
     * @param xCol The column's x-coordinate.
     *
     * @return True if the col is full, meaning it has no empty GridCell;
     * otherwise, false.
     */
    bool checkFullCol(int xCol) const;

    /**
     * @brief Sets each cell on the row at the given y-coordinate to empty
     * state.
     *
     * @param yRow The row's y-coordinate.
     */
    void emptyRow(int yRow);

    // NOTE: this is not required, but could be something to toggle,
    // e.g. for an "easy" mode or a temporary Bonus.
    /**
     * @brief Sets each cell on the column at the given x-coordinate to empty
     * state.
     *
     * @param xCol The column's x-coordinate.
     */
    void emptyCol(int xCol);

    // NOTE: this is not required, but could be something to toggle,
    // e.g. for an "easy" mode or a temporary Bonus.
    /**
     * @brief Makes every non-empty cell drop down until it stands
     * either above another non-empty cell or at the bottom row of the
     * grid.
     */
    void gravity();

    /**
     * @brief Returns true if all cells in the 2 by 2 square whose bottom left
     * corner is in x,y are occupied.
     */
    bool check2By2Occupied(int x, int y);

    /**
     * @brief Empties all the cells in the 2 by 2 square
     * whose bottom left corner is in x,y.
     */
    void empty2By2Square(int x, int y);

  public:
    // #### Constructors ####

    Board() = default;
    Board(const Board &) = default;
    Board(Board &&) = default;

    // #### Assignment ####

    Board &operator=(const Board &) = default;
    Board &operator=(Board &&) = default;

    // #### Destructor ####

    ~Board() = default;

    // #### Getters ####

    /**
     * @brief Returns a const reference to the GridCell
     * instance at (xCol, yRow) in the grid.
     *
     * @param xCol The column index.
     * @param yRow The row index.
     *
     * @return A const reference to the Gridcell located at
     * (xCol, yRow) in the board.
     */
    const GridCell &get(int xCol, int yRow) const;

    /**
     * @brief Returns the width of the grid.
     *
     * @return The width of the grid.
     */
    static constexpr size_t getWidth() noexcept { return width_; }

    /**
     * @brief Returns the height of the grid.
     *
     * @return The height of the grid.
     */
    static constexpr size_t getHeight() noexcept { return height_; }

    // #### Board Actions ####

    /**
     * @brief Places the given tetromino in the grid.
     *
     * @param tetromino A unique pointer to the tetromino to be placed.
     *
     * @note The Tetromino will no longer be accessible after this function
     * gets called, ensuring it cannot be moved after being placed in the
     * grid.
     */
    void placeTetromino(TetrominoPtr tetromino);

    /**
     * @brief Checks whether the cell at the given vec2 coordinate is in the
     * grid and is empty.
     */
    bool checkInGrid(const Vec2 &vec) const;

    /**
     * @brief Checks whether the specified Tetromino can fit in the grid given
     * its anchor-point and body.
     *
     * @param tetromino A reference to the Tetromino be checked.
     *
     * @return True if the given Tetromino fits; otherwise, false.
     */
    bool checkInGrid(const ATetromino &tetromino) const;

    /**
     * @brief Destroys a random 2 by 2 square in
     * which all the cells are occupied in the board if found.
     */
    void destroy2By2Occupied();

    // #### Penalty Rows ####

    /**
     * Adds penalty rows, making all rows go up.
     * If it causes blocks to go outside the Board, doesn't do anything and
     * returns false (meaning the player has lost).
     *
     * @return False if any occupied tile goes out of the board
     */
    bool receivePenaltyRows(size_t numPenalty = 1);

    // #### Update Board State ####

    /**
     * @brief Clears/Empties full rows, makes rows above the cleared row
     * drop one row down and returns a BoardUpdate object.
     *
     * @return A BoardUpdate object.
     */
    BoardUpdate update();

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    /**
     * @brief Serializes the Board to json.
     */
    nlohmann::json serialize() const;

    /**
     * @brief Deserializes the Board from json.
     */
    void deserialize(const nlohmann::json &j);

    /* ------------------------------------------------
     *          Test Fixture Class
     * ------------------------------------------------*/

    friend BoardTest;
};

#endif
