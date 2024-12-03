#include "tetromino_shapes.hpp"

#include "../coordinate/coordinate.hpp"
#include "tetromino.hpp"

// #### Z Shape ####

TetrominoZ::TetrominoZ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{-1, 0},
                                        Coordinate{-1, -1}, Coordinate{0, 1}},
                Tetromino::ZLSJT_KICK_DATA, TetrominoShape::Z) {}

// #### L Shape ####

TetrominoL::TetrominoL(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, -1},
                                        Coordinate{0, 1}, Coordinate{1, 1}},
                Tetromino::ZLSJT_KICK_DATA, TetrominoShape::L) {}

// #### O Shape ####

TetrominoO::TetrominoO(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, 1},
                                        Coordinate{1, 0}, Coordinate{1, 1}},
                Tetromino::O_KICK_DATA, TetrominoShape::O) {}

// #### S Shape ####

TetrominoS::TetrominoS(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, -1},
                                        Coordinate{1, 0}, Coordinate{1, 1}},
                Tetromino::ZLSJT_KICK_DATA, TetrominoShape::S) {}

// #### I Shape ####

TetrominoI::TetrominoI(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, -1}, Coordinate{0, 0},
                                        Coordinate{0, 1}, Coordinate{0, 2}},
                Tetromino::I_KICK_DATA, TetrominoShape::I) {}

// #### J Shape ####

TetrominoJ::TetrominoJ(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, -1},
                                        Coordinate{-1, -1}, Coordinate{0, 1}},
                Tetromino::ZLSJT_KICK_DATA, TetrominoShape::J) {}

// #### T Shape ####

TetrominoT::TetrominoT(Coordinate &&anchorPoint)
    : Tetromino(std::move(anchorPoint),
                std::vector<Coordinate>{Coordinate{0, 0}, Coordinate{0, -1},
                                        Coordinate{1, 0}, Coordinate{0, 1}},
                Tetromino::ZLSJT_KICK_DATA, TetrominoShape::T) {}
