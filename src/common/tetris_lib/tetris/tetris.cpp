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

void Tetris::updatePreviewTetromino() {
    previewTetromino_ = activeTetromino_->clone();
    while (checkCanDrop(*previewTetromino_)) {
        previewTetromino_->move(TetrominoMove::Down);
    }
}

void Tetris::resetLockDelay() { ticksSinceLockStart_ = 0; }

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
    resetLockDelay();

    if (!board_.checkInGrid(*activeTetromino_)) {
        for (auto &tetrisObserver : tetrisObservers_) {
            tetrisObserver->notifyLost();
        }
    } else {
        board_.placeTetromino(std::move(activeTetromino_));
        for (auto &tetrisObserver : tetrisObservers_) {
            tetrisObserver->notifyActiveTetrominoPlaced();
        }
    }
}

bool Tetris::checkEmptyCell(size_t xCol, size_t yRow) const {
    return board_.get(xCol, yRow).isEmpty();
}

void Tetris::fetchNewTetromino() {
    // The queue will refill itself if there are too few Tetrominos
    // inside. -> No need to do it here.
    activeTetromino_ = tetrominoQueue_.fetchNext();
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Constructors ####

Tetris::Tetris()
    : lockDelayTicksNum_{DEFAULT_LOCK_DELAY_TICKS_NUM},
      ticksSinceLockStart_{0} {
    fetchNewTetromino();
}

// #### TetrisObserver ####

void Tetris::addObserver(TetrisObserverPtr pTetrisObserver) {
    tetrisObservers_.push_back(pTetrisObserver);
}

void Tetris::removeObserver(TetrisObserverPtr pTetrisObserver) {
    std::erase(tetrisObservers_, pTetrisObserver);
}

// #### Event API ####

size_t Tetris::eventClockTick() {
    size_t numClearedRows = 0;

    if (!checkCanDrop(*activeTetromino_)) {
        if (ticksSinceLockStart_ >= lockDelayTicksNum_) {
            // lock-delay has expired -> must place active now
            placeActive();
            numClearedRows = board_.update().getNumClearedRows();
            fetchNewTetromino();
        } else {
            // lock-delay hasn't expired but a tick occured (don't place
            // active yet)
            ticksSinceLockStart_++;
        }
    } else {
        eventTryMoveActive(TetrominoMove::Down);
    }

    updatePreviewTetromino();

    return numClearedRows;
}

size_t Tetris::eventBigDrop() {
    while (checkCanDrop(*activeTetromino_)) {
        activeTetromino_->move(TetrominoMove::Down);
    }

    placeActive();
    size_t numClearedRows = board_.update().getNumClearedRows();
    fetchNewTetromino();

    updatePreviewTetromino();

    return numClearedRows;
}

size_t Tetris::eventTryMoveActive(TetrominoMove tetrominoMove) {
    size_t numClearedRows = 0;

    if (tetrominoMove == TetrominoMove::Down
        && !checkCanDrop(*activeTetromino_)) {
        placeActive();
        numClearedRows = board_.update().getNumClearedRows();

        fetchNewTetromino();
    } else {
        activeTetromino_->move(tetrominoMove);

        if (!board_.checkInGrid(*activeTetromino_)) {
            activeTetromino_->move(tetrominoMove, true);
        }
    }

    updatePreviewTetromino();

    return numClearedRows;
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

void Tetris::eventHoldNextTetromino() {
    if (holdTetromino_ == nullptr) {
        // If there is no hold, simply move the next to hold.
        holdTetromino_ = tetrominoQueue_.fetchNext();
    } else {
        // If there is a hold, swap it with next tetromino.
        std::swap(holdTetromino_, tetrominoQueue_.front());
    }
}

void Tetris::eventReceivePenaltyLines(int numPenalties) {
    bool hasLost = !board_.receivePenaltyLines(numPenalties);
    updatePreviewTetromino();
    if (hasLost) {
        for (auto &tetrisObserver : tetrisObservers_) {
            tetrisObserver->notifyLost();
        }
    }
}

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoQueue_.size();
}

void Tetris::insertNextTetromino(TetrominoPtr &&pTetromino) {
    tetrominoQueue_.insertNextTetromino(std::move(pTetromino));
}

TetrominoPtr Tetris::createTetromino(TetrominoShape tetrominoShape) {
    // I & T tetromino should have its anchorPoint one row above compared to
    // the others when spawned
    int spawnRow = (tetrominoShape == TetrominoShape::I
                    || tetrominoShape == TetrominoShape::T
                    || tetrominoShape == TetrominoShape::MiniTetromino)
                       ? Board::getHeight() - 1
                       : Board::getHeight() - 2;

    return ATetromino::makeTetromino(tetrominoShape,
                                     Vec2(Board::getWidth() / 2 - 1, spawnRow));
}

void Tetris::destroy2By2Occupied() { board_.destroy2By2Occupied(); }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json Tetris::serializeSelf(bool emptyBoard) const {
    return {{"activeTetromino",
             activeTetromino_ ? activeTetromino_->serialize() : nullptr},
            {"previewTetromino",
             previewTetromino_ ? previewTetromino_->serialize() : nullptr},
            {"holdTetromino",
             holdTetromino_ ? holdTetromino_->serialize() : nullptr},
            {"board", emptyBoard ? Board{}.serialize() : board_.serialize()},
            {"tetrominoQueue", tetrominoQueue_.serialize()}};
}

nlohmann::json Tetris::serializeExternal() const {
    return {
        {"board", board_.serialize()},
    };
}
