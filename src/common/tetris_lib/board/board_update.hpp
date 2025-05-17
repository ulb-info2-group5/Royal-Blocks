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
    // #### Constructors ####

    BoardUpdate();
    BoardUpdate(const BoardUpdate &) = default;
    BoardUpdate(BoardUpdate &&) = default;

    // #### Assignment ####

    BoardUpdate &operator=(const BoardUpdate &) = default;
    BoardUpdate &operator=(BoardUpdate &&) = default;

    // #### Destructor ####

    ~BoardUpdate() = default;

    // #### Getters ####

    /**
     * @brief Returns the number of rows cleared in this board update.
     *
     * @return Number of rows cleared in this board update.
     */
    size_t getNumClearedRows() const noexcept;

    /**
     * @brief Returns the number of columns cleared in this board update.
     *
     * @return Number of columns cleared in this board update.
     */
    size_t getNumClearedColumns() const noexcept;

    // #### Incrementing ####

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
