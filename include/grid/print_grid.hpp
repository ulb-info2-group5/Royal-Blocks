#ifndef PRINT_GRID_HPP
#define PRINT_GRID_HPP

#include "../../src/board/board.hpp"

void draw_grid(int rows, int cols);
void draw_cells(Board* board);
void draw_active(Tetromino* activeTetromino);
void draw_preview(Tetromino *previewTetromino);
void ncurses_refresh();
void print_score(size_t score, uint32_t gridWidth);
void print_debug(char* str, uint32_t gridWidth);
void define_pairs();
void print_colors();
int ncurses_init();
void ncurses_quit();

#endif