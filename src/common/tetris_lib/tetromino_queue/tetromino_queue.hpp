#ifndef TETROMINO_QUEUE_HPP
#define TETROMINO_QUEUE_HPP

#include <deque>

#include "../tetromino/abstract_tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"

class TetrominoQueue {
  private:
    std::deque<TetrominoPtr> queue_;
    static constexpr size_t NUM_SERIALIZED_TETROMINOES =
        static_cast<size_t>(TetrominoShape::NumBasicTetrominoShape);

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
