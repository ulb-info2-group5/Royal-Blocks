#ifndef TETRIS_OBSERVER_HPP
#define TETRIS_OBSERVER_HPP

struct TetrisObserver {
    virtual void notifyLost() = 0;

    virtual void notifyActiveTetrominoPlaced() = 0;
};

#endif // TETRIS_OBSERVER_HPP
