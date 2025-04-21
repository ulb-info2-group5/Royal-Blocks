#include "tetris.hpp"

#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../tetromino/abstract_tetromino.hpp"
#include "vec2/vec2.hpp"

#include <cstdint>
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

    for (const auto &relativeVec2 : tetromino.getBody()) {
        Vec2 absoluteCoord = anchorPoint + relativeVec2;
        if (!board_.checkInGrid(absoluteCoord)) {
            return false;
        }
    }

    return true;
}

void Tetris::placeActive() {
    resetLockDelay();
    canHold_ = true;

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
    return board_.get(static_cast<int>(xCol), static_cast<int>(yRow)).isEmpty();
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Constructors ####

Tetris::Tetris()
    : lockDelayTicksNum_{DEFAULT_LOCK_DELAY_TICKS_NUM}, ticksSinceLockStart_{0},
      canHold_{true} {
    activeTetromino_ = tetrominoQueue_.fetchNext();
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
            activeTetromino_ = tetrominoQueue_.fetchNext();
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
    activeTetromino_ = tetrominoQueue_.fetchNext();

    updatePreviewTetromino();

    return numClearedRows;
}

size_t Tetris::eventTryMoveActive(TetrominoMove tetrominoMove) {
    size_t numClearedRows = 0;

    if (tetrominoMove == TetrominoMove::Down
        && !checkCanDrop(*activeTetromino_)) {
        placeActive();
        numClearedRows = board_.update().getNumClearedRows();

        activeTetromino_ = tetrominoQueue_.fetchNext();
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

    for (uint8_t offsetTestIdx = 1;
         offsetTestIdx <= activeTetromino_->getNumOffsetTests();
         ++offsetTestIdx) {
        testTetromino = activeTetromino_->getNthOffsetTest(offsetTestIdx);

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

void Tetris::eventHoldActiveTetromino() {
    if (!canHold_) {
        return;
    }

    canHold_ = false;

    // Create a copy in order to make it be at the top of the board again
    TetrominoPtr newHoldTetromino =
        createTetromino(activeTetromino_->getShape());

    if (holdTetromino_ != nullptr) {
        activeTetromino_ = std::move(holdTetromino_);
    } else {
        activeTetromino_ = tetrominoQueue_.fetchNext();
    }

    holdTetromino_ = std::move(newHoldTetromino);

    updatePreviewTetromino();
}

void Tetris::eventReceivePenaltyRows(int numPenalties) {
    bool hasLost =
        !board_.receivePenaltyRows(static_cast<size_t>(numPenalties));
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
    return ATetromino::makeTetromino(
        tetrominoShape, getTetrominoInitialAnchorPoint(tetrominoShape));
}

Vec2 Tetris::getTetrominoInitialAnchorPoint(TetrominoShape tetrominoShape) {
    // I, T & mini-tetromino should have the anchorPoint one row above
    // compared to the others when spawned.
    int posY = Board::getHeight()
               - ((tetrominoShape == TetrominoShape::I
                   || tetrominoShape == TetrominoShape::T
                   || tetrominoShape == TetrominoShape::MiniTetromino)
                      ? 1
                      : 2);

    int posX = Board::getWidth() / 2 - 1;

    return Vec2{Vec2(posX, posY)};
}

void Tetris::destroy2By2Occupied() { board_.destroy2By2Occupied(); }

/* ------------------------------------------------
 *          Serialization
 * ------------------------------------------------*/

nlohmann::json Tetris::serializeSelf(bool emptyBoard) const {
    auto tetrominoSerialize =
        [emptyBoard](const TetrominoPtr &pTetromino) -> nlohmann::json {
        return (pTetromino == nullptr || emptyBoard) ? nullptr
                                                     : pTetromino->serialize();
    };

    nlohmann::json j_tetrominoQueue =
        emptyBoard ? TetrominoQueue{}.serialize() : tetrominoQueue_.serialize();
    nlohmann::json j_board =
        emptyBoard ? Board{}.serialize() : board_.serialize();

    return {{"activeTetromino", tetrominoSerialize(activeTetromino_)},
            {"previewTetromino", tetrominoSerialize(previewTetromino_)},
            {"holdTetromino", tetrominoSerialize(holdTetromino_)},
            {"board", j_board},
            {"tetrominoQueue", j_tetrominoQueue}};
}

nlohmann::json Tetris::serializeExternal() const {
    return {
        {"board", board_.serialize()},
    };
}
