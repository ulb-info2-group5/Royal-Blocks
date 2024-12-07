#include "tetris.hpp"

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "event.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <random>
#include <thread>

// #### Tetromino Actions ####

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
    if (checkCanDrop()) {
        activeTetromino_->move(direction);
    }
}

void Tetris::bigDrop() {
    while (checkCanDrop()) {
        activeTetromino_->move(Direction::Down);
    }
}

// #### Manage Preview Tetromino ####

// TODO: this is wrong if preview is outside of the grid, it will loop forever
// because of the first while condition
void Tetris::updatePreviewVertical() {
    while (!board_.checkInGrid(*previewTetromino_)) {
        previewTetromino_->move(Direction::Down, true); // go up
    }
    while (board_.checkInGrid(*previewTetromino_)) {
        previewTetromino_->move(Direction::Down); // go down
    }
}

// #### Placing and Dropping in Grid ####

bool Tetris::checkCanDrop() const {
    Coordinate anchorPoint = activeTetromino_->getAnchorPoint();

    anchorPoint.moveRow(1);

    Coordinate absoluteCoordinate;
    for (const auto &relativeCoordinate : activeTetromino_->getBody()) {
        absoluteCoordinate = anchorPoint + relativeCoordinate;
        if (!checkEmptyCell(absoluteCoordinate.getRow(),
                            absoluteCoordinate.getCol()))
            return false;
    }

    return true;
}

void Tetris::placeActive() {
    isAlive_ = board_.checkInGrid(*activeTetromino_);

    if (isAlive_) {
        board_.placeTetromino(std::move(activeTetromino_));
    }
}

// #### Tetromino Queue ####

void Tetris::fillTetrominoesQueue() {
    constexpr size_t numShapes =
        static_cast<size_t>(TetrominoShape::NumTetrominoShape);

    std::array<std::unique_ptr<Tetromino>, numShapes> tetrominos;

    for (size_t i = 0; i < numShapes; i++) {
        // I and T tetrominoes should have their anchorPoint  one row above the
        // others when spawned
        int spawnRow = (static_cast<TetrominoShape>(i) == TetrominoShape::I
                        or static_cast<TetrominoShape>(i) == TetrominoShape::T)
                           ? 0
                           : 1;

        tetrominos[i] = Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Coordinate(board_.getWidth() / 2 - 1, spawnRow));
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tetrominos.begin(), tetrominos.end(), g);

    for (auto &tetromino : tetrominos) {
        tetrominoesQueue_.push(std::move(tetromino));
    }
}

void Tetris::fetchNewTetromino() {
    if (tetrominoesQueue_.empty()) {
        fillTetrominoesQueue();
    }

    activeTetromino_ = std::move(tetrominoesQueue_.front());
    tetrominoesQueue_.pop();

    previewTetromino_ = std::make_unique<Tetromino>(*activeTetromino_);
    // TODO: update preview's position

    isAlive_ = board_.checkInGrid(*activeTetromino_);
}

// #### Constructor ####

Tetris::Tetris() { fetchNewTetromino(); }

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

EventType Tetris::getNextEvent() {
    EventType event;

    pthread_mutex_lock(&queueMutex_);

    if (!eventQueue_.empty()) {
        event = eventQueue_.front();
        eventQueue_.pop();
    } else {
        event = EventType::None;
    }

    pthread_mutex_unlock(&queueMutex_);

    return event;
}

// #### Tetris Loop ####

void Tetris::run() {
    EventType event;
    while (isAlive_) {
        switch (event) {

        case EventType::None:
            std::cout << "None" << std::endl;
            break;

        case EventType::ClockTick:
            std::cout << "ClockTick" << std::endl;
            // tryMoveActive(Direction::Down);
            break;

        case EventType::BigDrop:
            std::cout << "BigDrop" << std::endl;
            // bigDrop();
            break;

        case EventType::MoveDown:
            std::cout << "MoveDown" << std::endl;
            // tryMoveActive(Direction::Down);
            break;

        case EventType::MoveLeft:
            std::cout << "MoveLeft" << std::endl;
            // tryMoveActive(Direction::Left);
            break;

        case EventType::MoveRight:
            std::cout << "MoveRight" << std::endl;
            // tryMoveActive(Direction::Right);
            break;

        case EventType::RotateClockwise:
            std::cout << "RotateClockwise" << std::endl;
            // tryRotateActive(true);
            break;

        case EventType::RotateCounterClockwise:
            std::cout << "RotateCounterClockwise" << std::endl;
            // tryRotateActive(false);
            break;
        }

        // Do all the updates on the game here
        // (check if should place active Tetromino,
        // check for full rows etc)
        board_.update();
        bigDrop();

        if (!checkCanDrop()) {
            board_.placeTetromino(std::move(activeTetromino_));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

// #### Getters ####

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}

bool Tetris::checkEmptyCell(size_t rowIdx, size_t colIdx) const {
    return board_.get(rowIdx, colIdx).isEmpty();
}
