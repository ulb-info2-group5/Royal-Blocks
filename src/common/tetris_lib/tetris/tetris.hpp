#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "event_type.hpp"

#include <mutex>
#include <pthread.h>
#include <queue>
#include <sys/types.h>

class TetrisTest;

constexpr uint32_t DEFAULT_LOCK_DELAY_TICKS_NUM = 1;

/**
 * @class Tetris
 * @brief Represents a Tetris game, composed essentially of a Board and a
 * Tetromino object.
 *
 * The Tetris class handles the game state, including the active Tetromino and
 * events like rotation, movement, and clockTick, making the Tetromino drop
 * one block down. Events are managed through an event-queue API.
 */
class Tetris {
    size_t score_ = 0;
    bool isAlive_ = true;
    Board board_;
    TetrominoPtr activeTetromino_;
    TetrominoPtr previewTetromino_;
    std::queue<TetrominoPtr> tetrominoesQueue_;

    // TODO: move this to constructor ?
    uint32_t lock_delay_ticks_num_ = DEFAULT_LOCK_DELAY_TICKS_NUM;
    uint32_t ticks_since_lock_start_ = 0;

    std::mutex mutex_;

  private:
    // #### Tetromino Actions ####

    /**
     * @brief Rotates the active Tetromino if possible.
     *
     * @param rotateClockwise True to rotate clockwise, false for
     * counter-clockwise.
     */
    void tryRotateActive(bool rotateClockwise);

    /**
     * @brief Moves the active Tetromino in the given direction if possible.
     *
     * @param direction The direction to move the Tetromino.
     */
    void tryMoveActive(Direction direction);

    /**
     * @brief Drops the active Tetromino until it hits the bottom or an occupied
     * cell.
     */
    void bigDrop();

    // #### Preview-Tetromino ####

    /**
     * @brief Updates the preview-Tetromino's vertical component.
     */
    void updatePreviewVertical();

    // #### Tetromino: Placing and checking that it can drop ####

    /**
     * @brief Checks whether the given tetromino can be droppped.
     *
     * @param tetromino The tetromino to be checked.
     */
    bool checkCanDrop(const ATetromino &tetromino) const;

    /**
     * @brief Places the active tetromino where it currently is in the grid
     * and sets the isAlive flag to false if it was placed outside of the
     * grid.
     */
    void placeActive();

    // #### Tetrominoes Queue ####

    /**
     * @brief Enqueues 7 new randomly shuffled Tetrominoes.
     */
    void fillTetrominoesQueue();

    /**
     * @brief Fetches the next tetromino from the queue and sets it as the
     * active tetromino.
     *
     * If there are no tetrominoes left in the queue, the queue is re-filled
     * with 7 new tetrominoes.
     */
    void fetchNewTetromino();

    // #### Grid Checks ####

    /**
     * @brief Checks whether the cell at rowIdx, colIdx is empty.
     *
     * @param rowIdx The row index.
     * @param colIdx The col index.
     */
    bool checkEmptyCell(size_t rowIdx, size_t colIdx) const;

    // #### Penalties ####

    /**
     * @brief Adds penalty lines, sets isAlive flag to false if it made the
     * player lose.
     */
    void receivePenaltyLines(int numPenalties) {
        bool hasLost = board_.receivePenaltyLines(numPenalties);
        setIsAlive(!hasLost);
    }

  public:
    // #### Constructors ####

    Tetris() = default;
    Tetris(const Tetris &) = delete;
    Tetris(Tetris &&) = delete;

    // #### Assignment ####

    Tetris &operator=(const Tetris &) = delete;
    Tetris &operator=(Tetris &&) = delete;

    // #### Destructor ####

    ~Tetris() = default;

    // #### Event API ####

    /**
     * @brief Handles the given event.
     * @param event The event to add to the queue.
     */
    void sendEvent(EventType event);

    // #### Setters ####

    /**
     * @brief Thread-safe way of setting the isAlive member.
     *
     * @param isAlive The new isAlive value.
     */
    void setIsAlive(bool isAlive);

    // #### Getters ####

    /**
     * @brief Thread-safe way of getting the isAlive member.
     *
     * @return False if the game is over; otherwise, true.
     */
    bool getIsAlive();

    /**
     * @brief Returns the current score.
     *
     * @return The current score.
     */
    size_t getCurrentScore();

    /**
     * @brief Returns how many Tetrominoes are waiting in the queue.
     *
     * @return The size of the queue.
     */
    size_t getTetrominoesQueueSize() const;

    // #### Test Fixture Class ####

    friend TetrisTest;
};

#endif
