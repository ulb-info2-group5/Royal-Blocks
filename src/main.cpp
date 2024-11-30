#include "tetromino/tetromino.hpp"
#include "tetromino/tetromino_shapes.hpp"

#include <iostream>
#include <memory>

int main() {

    for (int i = 0; i < 7; i++) {

        std::unique_ptr<Tetromino> tetromino = Tetromino::makeTetromino(
            static_cast<TetrominoShape>(i), Coordinate(0, 0));

        tetromino->debugPrint();

        tetromino->tryRotate();
        tetromino->debugPrint();
        tetromino->tryRotate();
        tetromino->debugPrint();
        tetromino->tryRotate();
        tetromino->debugPrint();
        tetromino->tryRotate();

        tetromino->debugPrint();

        std::cout << std::endl;
    }
}
