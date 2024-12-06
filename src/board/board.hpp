#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/tetromino.hpp"
#include "grid_cell.hpp"
#include <array>
#include <cstddef>

// TODO: check checkInGrid again
// bool checkInGrid(const Tetromino &tetromino);

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
    virtual bool checkFullRow(size_t rowIdx);

    /**
     * @brief Sets each cell on the rowIndex-th row to empty state.
     */
    virtual void emptyRow(size_t rowIdx);

    /**
     * @brief Makes every non-empty cell drop down until it stands above
     * another cell which isn't or it stands on the bottom row of the grid.
     */
    virtual void gravity();

    // TODO: previously know as checkFullRow but it was doing more than
    // checking a row (deleting rows) -> renamed it
    /**
     * @brief Clears full rows and makes every levitating non-empty cell drop
     * down.
     */
    virtual void update();

  public:
    // #### Getters ####

    /**
     * @brief Returns a const reference to the GridCell instance at
     * (rowIdx, colIdx) in the grid.
     */
    const GridCell &get(size_t rowIdx, size_t colIdx);

    /**
     * @brief Returns the width of the grid.
     */
    size_t getWidth();

    /**
     * @brief Returns the height of the grid.
     */
    size_t getHeight();

    // #### Board Actions ####

    // NOTE: Previously know as freezeTetromino
    /**
     * @brief Places the tetromino in the grid.
     */
    virtual void placeTetromino(const Tetromino &tetromino);

    // #### Checks ####
    // NOTE: Haven't changed anything in terms of logic.
    /**
     * @brief Checks whether the specified Tetromino can fit within the
     * current grid position.
     */
    bool checkInGrid(Tetromino &tetromino);

    // #### Should not be here ####

    // NOTE: This should be handled by either Tetris or PlayerState and
    // using an actual Queue of Penalties (will need to write Penatly
    // class and its derivatives first)
    //
    // int queuePenalty(Penalty &penalty);
    // int executePenalty(Penalty &penalty);
};

#endif
