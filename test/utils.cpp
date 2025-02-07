#include "utils.hpp"

#include <memory>

void rotateTetrominoNTimes(std::unique_ptr<ATetromino> &tetromino,
                           bool rotateClockwise, int n) {
    for (int i = 0; i < n; i++) {
        tetromino->rotate(rotateClockwise);
    }
}
