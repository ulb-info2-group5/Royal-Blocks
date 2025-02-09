#include "tetris.hpp"

#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../tetromino/tetromino.hpp"

#include <algorithm>
#include <cstdlib>
#include <memory>

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

void Tetris::fetchNewTetromino() {
    // The queue will refill itself if there are too few Tetrominos
    // inside. -> No need to do it here.
    activeTetromino_ = std::move(tetrominoQueue_.fetchNext());
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

void Tetris::holdNextTetromino() {
    if (holdTetromino_ == nullptr) {
        // If there is no hold, simply move the next to hold.
        holdTetromino_ = std::move(tetrominoQueue_.fetchNext());
    } else {
        // If there is a hold, swap it with next tetromino.
        std::swap(holdTetromino_, tetrominoQueue_.front());
    }
}

void Tetris::eventReceivePenaltyLines(int numPenalties) {
    bool hasLost = board_.receivePenaltyLines(numPenalties);
    if (hasLost) {
        setIsAlive(false);
    }
}

// #### Setters ####

void Tetris::setIsAlive(bool isAlive) { isAlive_ = isAlive; }

// #### Getters ####

bool Tetris::getIsAlive() const { return isAlive_; }

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoQueue_.size();
}
