#include "tetromino_shapes.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino.hpp"

// #### Z Shape ####
TetrominoZ::TetrominoZ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{1, 1}, Coordinate{1, 2}}) {}

TetrominoShape TetrominoZ::getShape() const noexcept {
    return TetrominoShape::Z;
}

// #### L Shape ####
TetrominoL::TetrominoL(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 2}, Coordinate{1, 2},
                                        Coordinate{1, 1}, Coordinate{1, 0}}) {}

TetrominoShape TetrominoL::getShape() const noexcept {
    return TetrominoShape::L;
}

// #### O Shape ####
TetrominoO::TetrominoO(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{1, 0}, Coordinate{1, 1}}) {}

TetrominoShape TetrominoO::getShape() const noexcept {
    return TetrominoShape::O;
}

void TetrominoO::tryRotate() {} // O shape doesn't need to rotate

// #### S Shape ####
TetrominoS::TetrominoS(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 1}, Coordinate{0, 2},
                                        Coordinate{1, 0}, Coordinate{1, 1}}) {}

TetrominoShape TetrominoS::getShape() const noexcept {
    return TetrominoShape::S;
}

// #### I Shape ####
TetrominoI::TetrominoI(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{0, 2}, Coordinate{0, 3}}) {}

TetrominoShape TetrominoI::getShape() const noexcept {
    return TetrominoShape::I;
}

// #### J Shape ####
TetrominoJ::TetrominoJ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{1, 0},
                                        Coordinate{1, 1}, Coordinate{1, 2}}) {}

TetrominoShape TetrominoJ::getShape() const noexcept {
    return TetrominoShape::J;
}

// #### T Shape ####
TetrominoT::TetrominoT(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{0, 2}, Coordinate{1, 1}}) {}

TetrominoShape TetrominoT::getShape() const noexcept {
    return TetrominoShape::T;
}
