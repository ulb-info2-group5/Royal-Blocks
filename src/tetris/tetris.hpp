#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "event_type.hpp"

#include <memory>
#include <pthread.h>
#include <queue>

class TetrisTest;

/**
 * @class Tetris
 * @brief Represents a Tetris game, composed of a Board and a Tetromino object.
 *
 * The Tetris class handles the game state, including the active Tetromino and
 * events like rotation, movement, and clockTick, making the Tetromino drop
 * one block down. Events are managed through an event-queue API.
 */
class Tetris final {
    bool isAlive_ = true;
    bool inGracePeriod_ = false;
    bool newTetrasFirstTick_ = true; // could also be a uint32_t tickCount
    Board board_;
    std::unique_ptr<Tetromino> activeTetromino_;
    std::unique_ptr<Tetromino> previewTetromino_;
    std::queue<EventType> eventQueue_;
    std::queue<std::unique_ptr<Tetromino>> tetrominoesQueue_;
    pthread_mutex_t queueMutex_ = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t isAliveMutex_ = PTHREAD_MUTEX_INITIALIZER;

  private:
    // #### Tetromino Actions ####

    /**
     * @brief Rotates the active Tetromino if possible.
     *
     * @param rotateClockwise True to rotate clockwise, false for
     * counter-clockwise.
     */
    virtual void tryRotateActive(bool rotateClockwise);

    /**
     * @brief Moves the active Tetromino in the given direction if possible.
     *
     * @param direction The direction to move the Tetromino.
     */
    virtual void tryMoveActive(Direction direction);

    /**
     * @brief Drops the active Tetromino until it hits the bottom or an occupied
     * cell.
     */
    virtual void bigDrop();

    // #### Manage Preview-Tetromino ####

    /**
     * @brief Updates the preview Tetromino's vertical component.
     */
    virtual void updatePreviewVertical();

    // #### Placing and Dropping in Grid ####

    /**
     * @brief Checks whether the active tetromino can be droppped.
     */
    virtual bool checkCanDrop() const;

    /**
     * @brief Places the active tetromino where it currently is in the grid and
     * sets the isAlive flag to false if it was placed outside of the grid.
     */
    virtual void placeActive();

    // #### Tetrominoes Queue ####

    /**
     * @brief Enqueues 7 new randomly shuffled Tetrominoes.
     */
    virtual void fillTetrominoesQueue();

    /**
     * @brief Fetches the next tetromino from the queue and sets it as the
     * active tetromino.
     *
     * If there are no tetrominoes left in the queue, the queue is re-filled
     * with new tetrominoes.
     */
    virtual void fetchNewTetromino();

    // #### Event Queue Internals ####

    /**
     * @brief Fetches the next event from the event-queue.
     *
     * @return The next event to handle.
     */
    virtual EventType getNextEvent();

    // #### Grid Checks ####

    /**
     * @brief Checks whether the cell at rowIdx, colIdx is empty.
     *
     * @param rowIdx The row index.
     * @param colIdx The col index.
     */
    virtual bool checkEmptyCell(size_t rowIdx, size_t colIdx) const;

  public:
    // #### Constructor ####

    Tetris();

    // #### Event Queue API ####

    /**
     * @brief Adds the event to the event-queue.
     *
     * @param event The event to add to the queue.
     */
    virtual void addEvent(EventType event);

    // #### Tetris Loop ####

    /**
     * @brief Handles each event from the event-queue.
     */
    virtual void run();

    // #### IsAlive Flag Setter ####

    /**
     * @brief Thread-safe way of setting the isAlive member.
     *
     * @param isAlive The new isAlive value.
     */
    virtual void setIsAlive(bool isAlive);

    // #### Getters ####

    /**
     * @brief Thread-safe way of getting the isAlive.
     *
     * @return  False if the game is over, true otherwise.
     */
    virtual bool getIsAlive();

    /**
     * @brief Returns how many Tetrominoes are waiting in the queue.
     *
     * @return The size of the queue.
     */
    virtual size_t getTetrominoesQueueSize() const;

    // #### Test Fixture Class ####

    friend TetrisTest;
};

#endif
