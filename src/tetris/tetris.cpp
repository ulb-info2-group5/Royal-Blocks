#include "tetris.hpp"

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "event.hpp"

#include <cstdlib>
#include <pthread.h>
#include <thread>

void Tetris::tryRotateActive(bool rotateClockwise) {
    activeTetromino_->rotate(rotateClockwise);

    uint8_t testIdx;
    bool isValid = false;
    for (testIdx = 0; testIdx < activeTetromino_->getNumOfTests() and !isValid;
         testIdx++) {
        activeTetromino_ = activeTetromino_->getNthKick(testIdx);
        isValid = board_.checkInGrid(*activeTetromino_);
    }

    if (!isValid) {
        activeTetromino_->rotate(!rotateClockwise);
    }
}

void Tetris::tryMoveActive(Direction direction) {
    activeTetromino_->move(direction);
    if (!board_.checkInGrid(*activeTetromino_)) {
        activeTetromino_->move(direction, true); // reverse
    }
}

// NOTE: this supposes that the horizontal component of the active Tetromino is
// always right, which should be assured by tryMoveActive and tryRotateActive
void Tetris::updatePreviewHorizontal() {
    previewTetromino_->setAnchorPoint(activeTetromino_->getAnchorPoint());
}

// TODO: this is wrong if preview is outside of the grid, it will loop forever
// because of the first while condition
void Tetris::updatePreviewVertical() {
    while (!board_.checkInGrid(*previewTetromino_)) {
        previewTetromino_->move(Direction::down, true); // go up
    }
    while (board_.checkInGrid(*previewTetromino_)) {
        previewTetromino_->move(Direction::down); // go down
    }
}

bool Tetris::checkCanDrop() const {
    return (activeTetromino_->getAnchorPoint()
            != previewTetromino_->getAnchorPoint());
}

void Tetris::placeActive() {
    isAlive_ = board_.checkInGrid(*activeTetromino_);

    if (isAlive_) {
        board_.placeTetromino(*activeTetromino_);
    }
}

// #### Event Queue API ####

void Tetris::addQueueEvent(EventType event) {
    std::cout << "addEvent: waiting for lock" << std::endl;
    pthread_mutex_lock(&queueMutex_);
    std::cout << "addEvent: locking" << std::endl;
    eventQueue_.push(event);
    std::cout << "adding event" << std::endl;
    pthread_mutex_unlock(&queueMutex_);
    std::cout << "addEvent: unlocked" << std::endl;
}

// #### Tetris Loop ####

void Tetris::run() {
    // TODO: this should be while not quitting the game
    EventType event;
    bool queueIsEmpty = false;
    while (true) {
        // std::cout << "run: waiting for lock" << std::endl;
        pthread_mutex_lock(&queueMutex_);
        // std::cout << "run: locked" << std::endl;

        queueIsEmpty = eventQueue_.empty();

        if (!queueIsEmpty) {
            event = eventQueue_.front();
            eventQueue_.pop();
        }

        pthread_mutex_unlock(&queueMutex_);
        std::cout << "run: unlocked" << std::endl;

        if (queueIsEmpty) {
            std::cout << "run: queue was empty, continueing" << std::endl;
            continue;
        }

        switch (event) {
        case EventType::clockTick:
            std::cout << "clockTick" << std::endl;
            // tryMoveActive(Direction::down);
            break;
        case EventType::moveDown:
            std::cout << "moveDown" << std::endl;
            // tryMoveActive(Direction::down);
            break;
        case EventType::moveLeft:
            std::cout << "moveLeft" << std::endl;
            // tryMoveActive(Direction::left);
            break;
        case EventType::moveRight:
            std::cout << "moveRight" << std::endl;
            // tryMoveActive(Direction::right);
            break;
        case EventType::rotateClockwise:
            std::cout << "rotateClockwise" << std::endl;
            // tryRotateActive(true);
            break;
        case EventType::rotateCounterClockwise:
            std::cout << "rotateCounterClockwise" << std::endl;
            // tryRotateActive(false);
            break;
        }

        // Do all the updates on the game here
        // (check if should place active Tetromino,
        // check for full rows etc)

        // TODO: this can get skipped by the continue, we should probably avoid
        // this because it uses cpu for nothing
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void Tetris::enqueueRandomTetromino() {
    TetrominoShape newTetrominoShape = static_cast<TetrominoShape>(
        std::rand() % static_cast<int>(TetrominoShape::NUM_TETROMINOSHAPE));

    tetrominoQueue_.push(Tetromino::makeTetromino(
        newTetrominoShape,
        Coordinate(0, board_.getWidth()
                          / 2))); // TODO: check the anchorPoint parameter
}
