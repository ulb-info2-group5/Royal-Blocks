#ifndef TETROMINO_SHAPE_HPP
#define TETROMINO_SHAPE_HPP

#include "tetromino.hpp"

enum class TetrominoShape {
    Z,
    L,
    O,
    S,
    I,
    J,
    T,
    NUM_TETROMINOSHAPE,
};

// #### Z Shape ####

class TetrominoZ : public Tetromino {
  public:
    TetrominoZ(Coordinate &&anchorPoint);
};

// #### L Shape ####

class TetrominoL : public Tetromino {
  public:
    TetrominoL(Coordinate &&anchorPoint);
};

// #### O Shape ####

class TetrominoO : public Tetromino {
  public:
    TetrominoO(Coordinate &&anchorPoint);
};

// #### S Shape ####

class TetrominoS : public Tetromino {
  public:
    TetrominoS(Coordinate &&anchorPoint);
};

// #### I Shape ####

class TetrominoI : public Tetromino {
  public:
    TetrominoI(Coordinate &&anchorPoint);
};

// #### J Shape ####

class TetrominoJ : public Tetromino {
  public:
    TetrominoJ(Coordinate &&anchorPoint);
};

// #### T Shape ####

class TetrominoT : public Tetromino {
  public:
    TetrominoT(Coordinate &&anchorPoint);
};

#endif
