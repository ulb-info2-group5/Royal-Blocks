#ifndef PRINT_GRID_HPP
#define PRINT_GRID_HPP

#include "../../src/board/board.hpp"

void draw_grid(int rows, int cols);
void draw_cells(Board* board);
void draw_active(Tetromino* activeTetromino);
void define_pairs();
void print_colors();
int ncurses_init();
void ncurses_quit();

#endif