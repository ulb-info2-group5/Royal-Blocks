#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "event.hpp"

#include <memory>
#include <pthread.h>
#include <queue>

class Tetris {
    bool isAlive_;
    Board board_;
    std::unique_ptr<Tetromino> activeTetromino_;
    std::unique_ptr<Tetromino> previewTetromino_;
    std::queue<EventType> eventQueue_;
    std::queue<std::unique_ptr<Tetromino>> tetrominoesQueue_;
    pthread_mutex_t queueMutex_ = PTHREAD_MUTEX_INITIALIZER;

  private:
    // #### Tetromino Actions ####

    // TODO: direction in the docstring might not be the best word for this.
    /**
     * @brief Attempts to rotate the active Tetromino in right direction.
     */
    virtual void tryRotateActive(bool rotateClowise);

    /**
     * @brief Attempts to move the active Tetromino in the given direction.
     */
    virtual void tryMoveActive(Direction direction);

    // #### Manage Preview Tetromino ####

    /**
     * @brief Updates the preview Tetromino's horizontal component.
     */
    virtual void updatePreviewHorizontal();

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
     * @brief Places the active tetromino where it currently is and sets
     * isAlive to false if it was placed outside of the grid.
     */
    virtual void placeActive();

    // #### Tetrominoes Queue ####

    /**
     * @brief Enqueues 7 new randomly shuffled Tetrominoes.
     */
    virtual void fillTetrominoesQueue();

  public:
    // #### Constructor ####

    Tetris();

    // #### Event Queue API ####

    /**
     * @brief Adds the event to the event-queue.
     */
    virtual void addQueueEvent(EventType event);

    // #### Tetris Loop ####

    /**
     * @brief Handles each event from the event-queue.
     */
    virtual void run();

    // #### Getters ####

    /**
     * @brief Returns how many Tetrominoes are waiting in the queue.
     */
    virtual size_t getTetrominoesQueueSize();
};

#endif
