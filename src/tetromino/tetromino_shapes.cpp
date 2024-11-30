#include "tetromino_shapes.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino.hpp"

// #### Z Shape ####
TetrominoZ::TetrominoZ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{1, 1}, Coordinate{1, 2}}) {}

// #### L Shape ####
TetrominoL::TetrominoL(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 2}, Coordinate{1, 2},
                                        Coordinate{1, 1}, Coordinate{1, 0}}) {}

// #### O Shape ####
TetrominoO::TetrominoO(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{1, 0}, Coordinate{1, 1}}) {}

void TetrominoO::tryRotate() {} // O shape doesn't need to rotate

// #### S Shape ####
TetrominoS::TetrominoS(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 1}, Coordinate{0, 2},
                                        Coordinate{1, 0}, Coordinate{1, 1}}) {}

// #### I Shape ####
TetrominoI::TetrominoI(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{0, 2}, Coordinate{0, 3}}) {}

// #### J Shape ####
TetrominoJ::TetrominoJ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{1, 0},
                                        Coordinate{1, 1}, Coordinate{1, 2}}) {}

// #### T Shape ####
TetrominoT::TetrominoT(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{0, 2}, Coordinate{1, 1}}) {}
