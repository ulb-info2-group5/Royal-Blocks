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
        activeTetromino_->move(Direction::down);
    }
}

// #### Manage Preview Tetromino ####

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
        static_cast<size_t>(TetrominoShape::NUM_TETROMINOSHAPE);

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

// #### Tetris Loop ####

void Tetris::run() {
    // TODO: this should be while not quitting the game
    EventType event;
    bool queueIsEmpty = false;
    while (isAlive_) {
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

        case EventType::bigDrop:
            std::cout << "bigDrop" << std::endl;
            // bigDrop();
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

// #### Getters ####

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}

bool Tetris::checkEmptyCell(size_t rowIdx, size_t colIdx) const {
    return board_.get(rowIdx, colIdx).isEmpty();
}
