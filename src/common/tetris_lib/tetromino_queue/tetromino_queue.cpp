#include "tetromino_queue.hpp"
#include "../board/board.hpp"
#include "../tetromino/tetromino_shapes.hpp"

#include <algorithm>
#include <cassert>
#include <optional>
#include <random>

TetrominoQueue::TetrominoQueue() { refill(); }

void TetrominoQueue::refill() {
    constexpr size_t numShapes =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

    // generate array of Tetrominoes (ordered)
    std::array<TetrominoPtr, numShapes> tetrominoes;
    for (size_t i = 0; i < numShapes; i++) {
        // TODO: Check if we could solve this issue in the I tetromino's
        // constructor for a cleaner solution
        //
        // I tetromino should have its anchorPoint one row above compared to
        // the others when spawned
        int spawnRow = (static_cast<TetrominoShape>(i) == TetrominoShape::I
                        or static_cast<TetrominoShape>(i) == TetrominoShape::T)
                           ? Board::getHeight() - 1
                           : Board::getHeight() - 2;

        tetrominoes.at(i) = ATetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Vec2(Board::getWidth() / 2 - 1, spawnRow));
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

    std::optional<TetrominoPtr> pTetromino = pop();

    // if it's nullopt, then the queue was empty, which should never have
    // happened in the first place.
    // TODO: check that assert is fine here
    assert(pTetromino != std::nullopt);

    return std::move(pTetromino.value());
}
