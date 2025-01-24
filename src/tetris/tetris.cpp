#include "tetris.hpp"

#include "../board/board.hpp"
#include "../board/board_update.hpp"
#include "../grid/print_grid.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino/tetromino_shapes.hpp"
#include "event_type.hpp"

#include <algorithm>
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

// #### Manage Preview-Tetromino ####

void Tetris::updatePreviewVertical() {
    while (checkCanDrop(*previewTetromino_)) {
        previewTetromino_->move(Direction::Down); // go down
    }
}

// #### Placing and Dropping in Grid ####

bool Tetris::checkCanDrop(const Tetromino &tetromino) const {
    Vec2 anchorPoint = tetromino.getAnchorPoint();

    anchorPoint.moveY(-1);

    Vec2 absoluteVec2;
    for (const auto &relativeVec2 : tetromino.getBody()) {
        absoluteVec2 = anchorPoint + relativeVec2;

        if (absoluteVec2.getX() < 0 or absoluteVec2.getX() >= board_.getWidth()
            or absoluteVec2.getY() < 0
            or absoluteVec2.getY() >= board_.getHeight()
            or !checkEmptyCell(absoluteVec2.getX(), absoluteVec2.getY()))
            return false;
    }

    return true;
}

void Tetris::placeActive() {
    std::cout << "placeActive called" << std::endl;

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

        tetrominoes.at(i) =
            Tetromino::makeTetromino(static_cast<TetrominoShape>(i),
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

void Tetris::handleNextEvent() {

    EventType event = getNextEvent();

    switch (event) {
    case EventType::None:
        break;

    case EventType::ClockTick: {
        if (newTetrominosFirstTick_) newTetrominosFirstTick_ = false;
        tryMoveActive(Direction::Down);

        if (!checkCanDrop(*activeTetromino_)) {
            // FIXME
            // std::cout << "!checkCanDrop" << std::endl;

            if (!inGracePeriod_) inGracePeriod_ = true;
            else {

                placeActive();

                score_ += board_.update().getNumClearedRows();
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

        // #if ENABLE_TUI
        ncurses_quit();
        // #endif // ENABLE_TUI

        exit(0); //! VERY NOT GOOD but temporary <3
        break;
    }

    if (event != EventType::None) {
        previewTetromino_ = std::make_unique<Tetromino>(*activeTetromino_);
        updatePreviewVertical();

        // #if ENABLE_TUI
        draw_grid(board_.getWidth(), board_.getHeight());
        draw_cells(&board_); // BUG: this cause crash

        draw_preview(previewTetromino_.get());
        draw_active(activeTetromino_.get());
        print_debug("score :", board_.getWidth());
        print_score(score_, board_.getWidth());
        ncurses_refresh();
        // #endif // ENABLE_TUI
    }
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

    while (getIsAlive()) {

        // TODO: remove this (debug)
        // for (int y = 0; y < board_.getHeight(); y++) {
        //     for (int x = 0; x < board_.getWidth(); x++) {
        //         std::cout << ((board_.get(x, y).isEmpty()) ? "." : "#");
        //     }
        //     std::cout << std::endl;
        // }

        handleNextEvent();
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

size_t Tetris::getCurrentScore() { return score_; }

size_t Tetris::getTetrominoesQueueSize() const {
    return tetrominoesQueue_.size();
}
