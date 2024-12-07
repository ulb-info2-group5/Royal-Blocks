#include "tetromino_shapes.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino.hpp"

// #### Z Shape ####

TetrominoZ::TetrominoZ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {-1, 0}, {-1, -1}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::Z) {}

// #### L Shape ####

TetrominoL::TetrominoL(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {0, -1}, {0, 1}, {-1, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::L) {}

// #### O Shape ####

TetrominoO::TetrominoO(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {0, 1}, {-1, 0}, {-1, 1}},
                Tetromino::O_OFFSET_DATA, TetrominoShape::O) {}

// #### S Shape ####

TetrominoS::TetrominoS(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, 0}, {-1, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::S) {}

// #### I Shape ####

TetrominoI::TetrominoI(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, -1}, {0, 0}, {0, 1}, {0, 2}},
                Tetromino::I_OFFSET_DATA, TetrominoShape::I) {}

// #### J Shape ####

TetrominoJ::TetrominoJ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, -1}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::J) {}

// #### T Shape ####

TetrominoT::TetrominoT(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{{0, 0}, {0, -1}, {-1, 0}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::T) {
    // This tetromino should spawn in an upside down T shape
    for (size_t i = 0; i < 2; i++) {
        rotate(true);
    }
}
