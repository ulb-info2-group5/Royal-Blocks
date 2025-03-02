#include "tetromino_queue.hpp"
#include "../tetris/tetris.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "tetromino/tetromino.hpp"

#include <random>

TetrominoQueue::TetrominoQueue() { refill(); }

size_t TetrominoQueue::size() const noexcept { return queue_.size(); };

TetrominoPtr &TetrominoQueue::front() { return queue_.front(); }

void TetrominoQueue::refill() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> distrib(
        0, static_cast<int>(TetrominoShape::NumBasicTetrominoShape) - 1);

    while (queue_.size() < MINIMUM_ENQUEUED_NUM) {
        queue_.push_back(
            Tetris::createTetromino(static_cast<TetrominoShape>(distrib(gen))));
    }
}

TetrominoPtr TetrominoQueue::fetchNext() {
    refill();
    TetrominoPtr ret = std::move(queue_.front());
    queue_.pop_front();
    return ret;
}

void TetrominoQueue::insertNextTetromino(TetrominoPtr pTetromino) {
    queue_.emplace_front(std::move(pTetromino));
}
