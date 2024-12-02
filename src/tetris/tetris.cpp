#include "tetris.hpp"

#include "../board/board.hpp"
#include "../coordinate/coordinate.hpp"

void Tetris::tryRotateActive(bool rotateClowise, bool shouldOffset) {
    activeTetromino_->rotate(true);

    if (!shouldOffset) {
        return;
    }

    bool canOffset = false;

    // TODO:
    // Until one kick fits in the grid:
    // Ask the Tetromino what it looks like at its i-th kick, check if it fits
    // in the Board. If so then set canOffset to true.

    if (!canOffset) {
        activeTetromino_->rotate(!rotateClowise);
    }
}
