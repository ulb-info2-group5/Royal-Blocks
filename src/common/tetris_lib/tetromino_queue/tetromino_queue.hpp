#ifndef TETROMINO_QUEUE_HPP
#define TETROMINO_QUEUE_HPP

#include "../queue/queue.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"

class TetrominoQueue : public Queue<TetrominoPtr> {
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

    /* ------------------------------------------------
     *          Serialization
     * ------------------------------------------------*/

    nlohmann::json serialize() const {
        nlohmann::json j_queue = nlohmann::json::array();
        for (const auto &tetromino : queue_) {
            j_queue.push_back(tetromino ? tetromino->serialize() : nullptr);
        }
        return j_queue;
    }
};

#endif // TETROMINO_QUEUE_HPP
