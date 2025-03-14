#include "tetromino_queue.hpp"
#include "../tetris/tetris.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "tetromino/tetromino.hpp"

#include <random>

TetrominoQueue::TetrominoQueue() { refill(); }

size_t TetrominoQueue::size() const noexcept { return queue_.size(); };

TetrominoPtr &TetrominoQueue::front() { return queue_.front(); }

void TetrominoQueue::refill() {
    std::cerr << "in refill" << std::endl;
    constexpr size_t numShapes =
        static_cast<size_t>(TetrominoShape::NumBasicTetrominoShape);

    // avoid filling the queue if already enough tetrominoes inside
    if (queue_.size() >= numShapes) {
        return;
    }

    std::array<TetrominoPtr, numShapes> tetrominoes;
    for (size_t i = 0; i < numShapes; i++) {
        tetrominoes.at(i) =
            Tetris::createTetromino(static_cast<TetrominoShape>(i));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tetrominoes.begin(), tetrominoes.end(), g);

    for (auto &tetromino : tetrominoes) {
        queue_.push_back(std::move(tetromino));
    }
}

TetrominoPtr TetrominoQueue::fetchNext() {
    std::cerr << "in fetchNext" << std::endl;
    refill();
    std::cerr << "after refill" << std::endl;
    TetrominoPtr ret = std::move(queue_.front());
    queue_.pop_front();
    return ret;
}

void TetrominoQueue::insertNextTetromino(TetrominoPtr pTetromino) {
    queue_.emplace_front(std::move(pTetromino));
}

nlohmann::json TetrominoQueue::serialize() const {
    nlohmann::json j_queue = nlohmann::json::array();

    for (const auto &tetromino :
         queue_ | std::views::take(NUM_SERIALIZED_TETROMINOES)) {
        j_queue.push_back(tetromino ? tetromino->serialize() : nullptr);
    }

    return j_queue;
}
