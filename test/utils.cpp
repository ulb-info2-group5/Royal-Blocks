#include "utils.hpp"

#include "../src/tetromino/tetromino.hpp"

#include <memory>

void rotateTetrominoNTimes(std::unique_ptr<Tetromino> &tetromino,
                           bool rotateClockwise, int n) {
    for (size_t i = 0; i < n; i++) {
        tetromino->rotate(rotateClockwise);
    }
}
