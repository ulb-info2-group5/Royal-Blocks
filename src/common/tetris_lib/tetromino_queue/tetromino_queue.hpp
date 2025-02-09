#ifndef TETROMINO_QUEUE_HPP
#define TETROMINO_QUEUE_HPP

#include "../serializable_queue/serializable_queue.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"

class TetrominoQueue : public SerializableQueue<TetrominoPtr> {
    static constexpr size_t MINIMUM_ENQUEUED_NUM =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

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

    TetrominoPtr fetchNext();
};

#endif // TETROMINO_QUEUE_HPP
