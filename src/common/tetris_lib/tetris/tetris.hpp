#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"
#include "../tetromino_queue/tetromino_queue.hpp"
#include "tetromino/tetromino_shapes.hpp"

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
    bool isAlive_ = true;
    TetrominoPtr activeTetromino_;
    TetrominoPtr previewTetromino_;
    Board board_;

    TetrominoPtr holdTetromino_;
    TetrominoQueue tetrominoQueue_;

    // TODO: move this to constructor ?
    uint32_t lock_delay_ticks_num_ = DEFAULT_LOCK_DELAY_TICKS_NUM;
    uint32_t ticks_since_lock_start_ = 0;

  private:
    // #### Preview Tetromino ####

    /**
     * @brief Updates the preview tetromino.
     */
    void updatePreviewTetromino();

    // #### Checks helper ####

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

    /**
     * @brief Checks whether the cell at the given position is empty.
     *
     * @param xCol The x-coordinate.
     * @param yRow The y-coordinate.
     */
    bool checkEmptyCell(size_t xCol, size_t yRow) const;

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
     * @brief Makes the active Tetromino go down (and manages the lock delay).
     * Also updates the board to clear the fullRows and returns how many rows
     * were cleared.
     */
    size_t eventClockTick();

    /**
     * @brief Drops the active Tetromino until it hits the bottom or an occupied
     * cell.
     */
    void eventBigDrop();

    /**
     * @brief Moves the active Tetromino in the given direction if possible.
     *
     * @param tetrominoMove The direction to move the Tetromino.
     */
    void eventTryMoveActive(TetrominoMove tetrominoMove);

    /**
     * @brief Rotates the active Tetromino if possible.
     *
     * @param rotateClockwise True to rotate clockwise, false for
     * counter-clockwise.
     */
    void eventTryRotateActive(bool rotateClockwise);

    /**
     * @brief Moves the next Tetromino from the queue to hold.
     *
     * If there was no hold tetromino, move the tetromino to hold.
     * If there was a hold tetromino, swap it with the tetromino to hold.
     */
    void eventHoldNextTetromino();

    /**
     * @brief Adds penalty lines, sets isAlive flag to false if it made the
     * player lose.
     */
    void eventReceivePenaltyLines(int numPenalties);

    // #### Setter ####

    /**
     * @brief Sets the isAlive member.
     *
     * @param isAlive The new isAlive value.
     */
    void setIsAlive(bool isAlive);

    // #### Getters ####

    /**
     * @brief Gets the isAlive member.
     *
     * @return False if the game is over; otherwise, true.
     */
    bool getIsAlive() const;

    /**
     * @brief Returns how many Tetrominoes are waiting in the queue.
     *
     * @return The size of the queue.
     */
    size_t getTetrominoesQueueSize() const;

    /**
     * @brief Inserts the given tetromino at the front of the tetrominoes queue.
     */
    void insertNextTetromino(TetrominoPtr pTetromino) {
        tetrominoQueue_.insertNextTetromino(std::move(pTetromino));
    }

    static TetrominoPtr createTetromino(TetrominoShape tetrominoShape);

    // #### Test Fixture Class ####

    friend TetrisTest;
};

#endif
