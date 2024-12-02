// NOTE: This is a temporary Board definition, will be replaced by the complete
// Board once it is ready (Just so that my LSP doesn't yell because of missing
// Board class...)

#ifndef BOARD_HPP
#define BOARD_HPP

#include "../tetromino/tetromino.hpp"

class Board {
  public:
    bool checkInGrid(const Tetromino &tetromino);
};

#endif
