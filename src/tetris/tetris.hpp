#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "../board/board.hpp"
#include "../tetromino/tetromino.hpp"

#include <memory>

class Tetris {
    Board board_;
    std::unique_ptr<Tetromino> activeTetromino_;

  private:
    virtual bool offsetActive(int oldRotationIdx, int newRotationIdx);

  public:
    virtual void tryRotateActive(bool rotateClowise, bool shouldOffset);
    virtual void tryMoveActive(Direction direction);
};

#endif
