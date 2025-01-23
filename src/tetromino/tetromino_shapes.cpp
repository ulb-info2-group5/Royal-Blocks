#include "tetromino_shapes.hpp"

#include "../vec2/vec2.hpp"
#include "tetromino.hpp"

/*--------------------------------------------------
             TetrominoShapes
--------------------------------------------------*/

// #### Output Stream ####

std::ostream &operator<<(std::ostream &os, TetrominoShape shape) {
    switch (shape) {
    case TetrominoShape::Z:
        os << "Z";
        break;
    case TetrominoShape::L:
        os << "L";
        break;
    case TetrominoShape::O:
        os << "O";
        break;
    case TetrominoShape::S:
        os << "S";
        break;
    case TetrominoShape::I:
        os << "I";
        break;
    case TetrominoShape::J:
        os << "J";
        break;
    case TetrominoShape::T:
        os << "T";
        break;
    case TetrominoShape::NumTetrominoShape:
        os << "NumTetrominoShape";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}

/*--------------------------------------------------
             Tetromino's Derivatives
--------------------------------------------------*/

// #### Z Shape ####

TetrominoZ::TetrominoZ(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {-1, 0}, {-1, -1}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::Z) {}

// #### L Shape ####

TetrominoL::TetrominoL(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {0, -1}, {0, 1}, {-1, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::L) {}

// #### O Shape ####

TetrominoO::TetrominoO(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {0, 1}, {-1, 0}, {-1, 1}},
                Tetromino::O_OFFSET_DATA, TetrominoShape::O) {}

// #### S Shape ####

TetrominoS::TetrominoS(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {0, -1}, {-1, 0}, {-1, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::S) {}

// #### I Shape ####

TetrominoI::TetrominoI(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, -1}, {0, 0}, {0, 1}, {0, 2}},
                Tetromino::I_OFFSET_DATA, TetrominoShape::I) {}

// #### J Shape ####

TetrominoJ::TetrominoJ(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {0, -1}, {-1, -1}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::J) {}

// #### T Shape ####

TetrominoT::TetrominoT(Vec2 &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Vec2>{{0, 0}, {0, -1}, {-1, 0}, {0, 1}},
                Tetromino::ZLSJT_OFFSET_DATA, TetrominoShape::T) {
    // This tetromino should spawn in an upside down T shape
    for (size_t i = 0; i < 2; i++) {
        rotate(true);
    }
}
