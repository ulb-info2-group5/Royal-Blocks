#ifndef TETRIS_OBSERVER_HPP
#define TETRIS_OBSERVER_HPP

struct TetrisObserver {
    TetrisObserver() = default;
    TetrisObserver(const TetrisObserver &) = default;
    TetrisObserver(TetrisObserver &&) = default;
    TetrisObserver &operator=(const TetrisObserver &) = default;
    TetrisObserver &operator=(TetrisObserver &&) = default;

    virtual ~TetrisObserver() = default;

    virtual void notifyLost() = 0;

    virtual void notifyActiveTetrominoPlaced() = 0;
};

#endif // TETRIS_OBSERVER_HPP
