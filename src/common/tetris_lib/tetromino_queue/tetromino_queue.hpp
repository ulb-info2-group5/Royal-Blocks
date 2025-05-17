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

#ifndef TETROMINO_QUEUE_HPP
#define TETROMINO_QUEUE_HPP

#include <deque>

#include "../tetromino/abstract_tetromino.hpp"

class TetrominoQueue {
  private:
    std::deque<TetrominoPtr> queue_;
    static constexpr size_t NUM_SERIALIZED_TETROMINOES = 6;

  public:
    TetrominoQueue();
    TetrominoQueue(const TetrominoQueue &) = default;
    TetrominoQueue(TetrominoQueue &&) = default;
    TetrominoQueue &operator=(const TetrominoQueue &) = default;
    TetrominoQueue &operator=(TetrominoQueue &&) = default;

    ~TetrominoQueue() = default;

    /**
     * @brief Returns the queue's size.
     */
    size_t size() const noexcept;

    /**
     * @brief Returns a mutable reference to the element at the front of the
     * queue.
     */
    TetrominoPtr &front();

    /**
     * @brief Pushes randomly shuffled tetrominoes in the queue (one of each
     * shape).
     */
    void refill();

    /**
     * @brief Returns the next tetromino from the queue and removes it from the
     * queue.
     */
    TetrominoPtr fetchNext();

    /**
     * @brief Inserts the given tetromino at the front of the queue.
     */
    void insertNextTetromino(TetrominoPtr pTetromino);

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const;
};

#endif // TETROMINO_QUEUE_HPP
