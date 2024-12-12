#include "tetris.hpp"

#include "../../include/grid/print_grid.hpp"
#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "event_type.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <pthread.h>
#include <random>

/*--------------------------------------------------
                     PRIVATE
--------------------------------------------------*/

// #### Tetromino Actions ####

void Tetris::tryRotateActive(bool rotateClockwise) {
    activeTetromino_->rotate(rotateClockwise);

    std::unique_ptr<Tetromino> testTetromino;

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
    while (checkCanDrop()) {
        activeTetromino_->move(Direction::Down);
    }
}

// #### Manage Preview-Tetromino ####

// TODO: this is wrong if preview is outside of the grid, it will loop
// forever because of the first while condition
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

        if (absoluteCoordinate.getCol() < 0
            or absoluteCoordinate.getCol() >= board_.getWidth()
            or absoluteCoordinate.getRow() < 0
            or absoluteCoordinate.getRow() >= board_.getHeight()
            or !checkEmptyCell(absoluteCoordinate.getRow(),
                               absoluteCoordinate.getCol()))
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

    std::array<std::unique_ptr<Tetromino>, numShapes> tetrominoes;

    for (size_t i = 0; i < numShapes; i++) {
        // I tetromino should have its anchorPoint one row above compared to
        // the others when spawned
        int spawnRow = (static_cast<TetrominoShape>(i) == TetrominoShape::I
                        or static_cast<TetrominoShape>(i) == TetrominoShape::T)
                           ? 0
                           : 1;

        tetrominoes.at(i) = Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i),
            Coordinate(spawnRow, board_.getWidth() / 2 - 1));
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

    previewTetromino_ = std::make_unique<Tetromino>(*activeTetromino_);
    // TODO: update preview's position
}

// #### Event Queue Internals ####

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

// #### Grid Checks ####

bool Tetris::checkEmptyCell(size_t rowIdx, size_t colIdx) const {
    return board_.get(rowIdx, colIdx).isEmpty();
}

/*--------------------------------------------------
                     PUBLIC
--------------------------------------------------*/

// #### Constructor ####

Tetris::Tetris() = default;

// #### Destructor ####

Tetris::~Tetris() = default;

// #### Event Queue API ####

void Tetris::addEvent(EventType event) {
    pthread_mutex_lock(&queueMutex_);
    eventQueue_.push(event);
    pthread_mutex_unlock(&queueMutex_);
}

// #### Tetris Loop ####

void Tetris::run() {
    EventType event;

    fetchNewTetromino();

    constexpr float frequency = 60;
    constexpr std::chrono::duration period =
        std::chrono::seconds(1) / frequency;

    size_t height = board_.getHeight();
    size_t width = board_.getWidth();

    while (getIsAlive()) {

        event = getNextEvent();

        switch (event) {
        case EventType::None:
            break;

        case EventType::ClockTick: {
            if (newTetrominosFirstTick_) newTetrominosFirstTick_ = false;
            tryMoveActive(Direction::Down);

            if (!checkCanDrop()) {
                if (!inGracePeriod_) inGracePeriod_ = true;
                else {
                    placeActive();
                    BoardUpdate boardUpdate = board_.update();
                    fetchNewTetromino();
                    newTetrominosFirstTick_ = true;
                }
            } else {
                if (inGracePeriod_) inGracePeriod_ = false;
            }
            break;
        }

        case EventType::BigDrop:
            bigDrop();

            //! WILL CAUSES CLIENT SERVER GAME TICK DESYNC BUT ALLOWS BETTER
            //! GAME EXPERIENCE
            addEvent(EventType::ClockTick);

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
            ncurses_quit();
            exit(0); //! VERY NOT GOOD but temporary <3
            break;
        }

        if (event != EventType::None) {
            draw_grid(height, width);
            draw_cells(&board_);
            draw_active(activeTetromino_.get());
            print_debug("uwu :3 aur aur\n test line2\n "
                        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
                        width);
        }
    }
    ncurses_quit();
    std::cout << "Game Over" << std::endl;
}

// #### IsAlive Flag Internals ####

void Tetris::setIsAlive(bool isAlive) {
    pthread_mutex_lock(&isAliveMutex_);
    isAlive_ = isAlive;
    pthread_mutex_unlock(&isAliveMutex_);
}

// #### Getters ####

bool Tetris::getIsAlive() {
    pthread_mutex_lock(&isAliveMutex_);
    bool isAlive = isAlive_;
    pthread_mutex_unlock(&isAliveMutex_);
    return isAlive;
}

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}
