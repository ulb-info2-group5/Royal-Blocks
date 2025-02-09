#include "tetris.hpp"

#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <random>

/*--------------------------------------------------
                     PRIVATE
--------------------------------------------------*/

// #### Preview Tetromino ####

void Tetris::updatePreviewTetromino() {
    previewTetromino_ = activeTetromino_->clone();
    while (checkCanDrop(*previewTetromino_)) {
        previewTetromino_->move(Direction::Down);
    }
}

// #### Checks helper ####

bool Tetris::checkCanDrop(const ATetromino &tetromino) const {
    Vec2 anchorPoint = tetromino.getAnchorPoint();

    anchorPoint.moveY(-1);

    Vec2 absoluteVec2;
    for (const auto &relativeVec2 : tetromino.getBody()) {
        absoluteVec2 = anchorPoint + relativeVec2;

        if (absoluteVec2.getX() < 0
            or absoluteVec2.getX() >= static_cast<int>(board_.getWidth())
            or absoluteVec2.getY() < 0
            or absoluteVec2.getY() >= static_cast<int>(board_.getHeight())
            or !checkEmptyCell(absoluteVec2.getX(), absoluteVec2.getY()))
            return false;
    }

    return true;
}

void Tetris::placeActive() {
    setIsAlive(board_.checkInGrid(*activeTetromino_));

    if (getIsAlive()) {
        board_.placeTetromino(std::move(activeTetromino_));
    }
}

bool Tetris::checkEmptyCell(size_t xCol, size_t yRow) const {
    return board_.get(xCol, yRow).isEmpty();
}

// #### Tetrominoes Queue ####

void Tetris::fillTetrominoesQueue() {
    constexpr size_t numShapes =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

    std::array<TetrominoPtr, numShapes> tetrominoes;

    for (size_t i = 0; i < numShapes; i++) {
        // I tetromino should have its anchorPoint one row above compared to
        // the others when spawned
        int spawnRow = (static_cast<TetrominoShape>(i) == TetrominoShape::I
                        or static_cast<TetrominoShape>(i) == TetrominoShape::T)
                           ? board_.getHeight() - 1
                           : board_.getHeight() - 2;

        tetrominoes.at(i) = ATetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Vec2(board_.getWidth() / 2 - 1, spawnRow));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tetrominoes.begin(), tetrominoes.end(), g);

    for (auto &tetromino : tetrominoes) {
        tetrominoesQueue_.push(std::move(tetromino));
    }
}

void Tetris::fetchNewTetromino() {
    if (tetrominoesQueue_.empty()) {
        fillTetrominoesQueue();
    }

    activeTetromino_ = std::move(tetrominoesQueue_.front());
    tetrominoesQueue_.pop();
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Event API ####

size_t Tetris::eventClockTick() {
    size_t numClearedRows = 0;

    if (!checkCanDrop(*activeTetromino_)) {
        if (ticks_since_lock_start_ >= lock_delay_ticks_num_) {
            // lock-delay has expired -> must place active now
            placeActive();
            numClearedRows = board_.update().getNumClearedRows();
            fetchNewTetromino();

            // reset lock delay for next time
            ticks_since_lock_start_ = 0;
        } else {
            // lock-delay hasn't expired but a tick occured (don't place active
            // yet)
            ticks_since_lock_start_++;
        }
    } else {
        eventTryMoveActive(Direction::Down);
    }

    updatePreviewTetromino();

    return numClearedRows;
}

void Tetris::eventBigDrop() {
    while (checkCanDrop(*activeTetromino_)) {
        activeTetromino_->move(Direction::Down);
    }

    updatePreviewTetromino();
}

void Tetris::eventTryMoveActive(Direction direction) {
    activeTetromino_->move(direction);

    if (!board_.checkInGrid(*activeTetromino_)) {
        activeTetromino_->move(direction, true);
    }

    updatePreviewTetromino();
}

void Tetris::eventTryRotateActive(bool rotateClockwise) {
    activeTetromino_->rotate(rotateClockwise);

    TetrominoPtr testTetromino;

    bool isValid = false;

    for (size_t testIdx = 1; testIdx <= activeTetromino_->getNumOfTests();
         ++testIdx) {
        testTetromino = activeTetromino_->getNthOffset(testIdx);

        if (board_.checkInGrid(*testTetromino)) {
            activeTetromino_ = std::move(testTetromino);
            isValid = true;
            break;
        }
    }

    if (!isValid) {
        activeTetromino_->rotate(!rotateClockwise);
    }

    updatePreviewTetromino();
}

void Tetris::eventReceivePenaltyLines(int numPenalties) {
    bool hasLost = board_.receivePenaltyLines(numPenalties);
    setIsAlive(!hasLost);
}

// #### Setters ####

void Tetris::setIsAlive(bool isAlive) { isAlive_ = isAlive; }

// #### Getters ####

bool Tetris::getIsAlive() const { return isAlive_; }

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}
