#include "tetris.hpp"

#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "event_type.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <pthread.h>
#include <random>

/*--------------------------------------------------
                     PRIVATE
--------------------------------------------------*/

// #### Tetromino Actions ####

void Tetris::tryRotateActive(bool rotateClockwise) {
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
}

void Tetris::tryMoveActive(Direction direction) {
    activeTetromino_->move(direction);

    if (!board_.checkInGrid(*activeTetromino_)) {
        activeTetromino_->move(direction, true);
    }
}

void Tetris::bigDrop() {
    while (checkCanDrop(*activeTetromino_)) {
        activeTetromino_->move(Direction::Down);
    }
}

// #### Preview-Tetromino ####

void Tetris::updatePreviewVertical() {
    while (checkCanDrop(*previewTetromino_)) {
        previewTetromino_->move(Direction::Down);
    }
}

// #### Tetromino: Placing and checking that it can drop ####

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

// #### Grid Checks ####

bool Tetris::checkEmptyCell(size_t rowIdx, size_t colIdx) const {
    return board_.get(rowIdx, colIdx).isEmpty();
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Event API ####

void Tetris::sendEvent(EventType event) {
    std::lock_guard<std::mutex> lock(mutex_);

    switch (event) {
    case EventType::None:
        break;

    case EventType::ClockTick: {
        if (!checkCanDrop(*activeTetromino_)) {
            if (ticks_since_lock_start_ >= lock_delay_ticks_num_) {
                // lock-delay has expired -> must place active now
                placeActive();
                score_ += board_.update().getNumClearedRows();
                fetchNewTetromino();

                ticks_since_lock_start_ = 0;
            } else {
                ticks_since_lock_start_++;
            }
        } else {
            tryMoveActive(Direction::Down);
        }

        break;
    }

    case EventType::BigDrop:
        bigDrop();
        // NOTE: Could add a lock_delay here
        break;

    case EventType::MoveDown:
        tryMoveActive(Direction::Down);
        break;

    case EventType::MoveLeft:
        tryMoveActive(Direction::Left);
        break;

    case EventType::MoveRight:
        tryMoveActive(Direction::Right);
        break;

    case EventType::RotateClockwise:
        tryRotateActive(true);
        break;

    case EventType::RotateCounterClockwise:
        tryRotateActive(false);
        break;

    case EventType::Quit:
        // TODO:: When the player quits, we should make him loose instantly and
        // disconnect him but it shouldn't be handled here.
        setIsAlive(false);
        break;
    }

    if (event != EventType::None) {
        previewTetromino_ = activeTetromino_->clone();
        updatePreviewVertical();
    }
}

// #### Setters ####

void Tetris::setIsAlive(bool isAlive) {
    std::lock_guard<std::mutex> lock(mutex_);
    isAlive_ = isAlive;
}

// #### Getters ####

bool Tetris::getIsAlive() {
    std::lock_guard<std::mutex> lock(mutex_);
    return isAlive_;
}

size_t Tetris::getCurrentScore() { return score_; }

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}
