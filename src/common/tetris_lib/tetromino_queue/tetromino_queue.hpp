#ifndef TETROMINO_QUEUE_HPP
#define TETROMINO_QUEUE_HPP

#include "../serializable_queue/serializable_queue.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"

class TetrominoQueue : public SerializableQueue<TetrominoPtr> {
    static constexpr size_t MINIMUM_ENQUEUED_NUM =
        static_cast<size_t>(TetrominoShape::NumBasicTetrominoShape);

  public:
    TetrominoQueue();
    TetrominoQueue(const TetrominoQueue &) = default;
    TetrominoQueue(TetrominoQueue &&) = default;
    TetrominoQueue &operator=(const TetrominoQueue &) = default;
    TetrominoQueue &operator=(TetrominoQueue &&) = default;

    ~TetrominoQueue() = default;

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
};

#endif // TETROMINO_QUEUE_HPP
