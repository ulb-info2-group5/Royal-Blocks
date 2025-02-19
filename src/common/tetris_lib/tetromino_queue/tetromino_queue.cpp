#include "tetromino_queue.hpp"
#include "../board/board.hpp"
#include "../tetris/tetris.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "tetromino/tetromino.hpp"

#include <algorithm>
#include <cassert>
#include <optional>
#include <random>

TetrominoQueue::TetrominoQueue() { refill(); }

void TetrominoQueue::refill() {
    constexpr size_t numShapes =
        static_cast<size_t>(TetrominoShape::NumBasicTetrominoShape);

    // generate array of Tetrominoes (ordered)
    std::array<TetrominoPtr, numShapes> tetrominoes;
    for (size_t i = 0; i < numShapes; i++) {
        tetrominoes.at(i) =
            Tetris::createTetromino(static_cast<TetrominoShape>(i));
    }

    // shuffle the array of Tetrominoes
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tetrominoes.begin(), tetrominoes.end(), g);

    // Push the Tetrominoes in the queue
    for (auto &tetromino : tetrominoes) {
        queue_.emplace_back(std::move(tetromino));
    }
}

TetrominoPtr TetrominoQueue::fetchNext() {
    if (queue_.size() > MINIMUM_ENQUEUED_NUM) {
        refill();
    }

    std::optional<TetrominoPtr> pTetromino = popFront();

    // if it's nullopt, then the queue was empty, which should never have
    // happened in the first place.
    // TODO: check that assert is fine here
    assert(pTetromino != std::nullopt);

    return std::move(pTetromino.value());
}

void TetrominoQueue::insertNextTetromino(TetrominoPtr pTetromino) {
    queue_.emplace_front(std::move(pTetromino));
}
