
#include <ncurses.h>

// #include "../../include/board/grid_cell.hpp"
// #include "../../include/board/board.hpp"
#include "../board/grid_cell.hpp"
#include "../board/board.hpp"




void draw_grid(int rows, int cols) {

	for(uint32_t y=0; y<rows; y++){
		mvaddch(y+1, 0, '|');
		mvaddch(y+1, 2*(cols+1)-1, '|');
	}
	for(uint32_t x=0; x<2*cols; x++){
		mvaddch(0, x+1, '-');
		mvaddch(rows+2-1, x+1, '-');
	}
	/*<3*/

    mvaddch(0, 0, '+');
    mvaddch(0, (cols*2)+1, '+');
    mvaddch((rows+1), 0, '+');
    mvaddch((rows+1), (cols*2)+1, '+');
	/*<3*/

	refresh();
}


void draw_cells(Board* board){
	uint32_t height = board->getHeight();
	uint32_t width = board->getWidth();
	GridCell gc;
	for(uint32_t y=0; y<height; y++){
		for(uint32_t x=0; x<width; x++){
			gc = board->get(y, x);
			// printf("isEmpty ? : %1x\n", gc.isEmpty());
			if(!gc.isEmpty()){
				// mvaddch(x+1, y+1, ' ' | COLOR_PAIR(gc.getColorId()));
				mvaddch(y+1, (2*x)+1, ' ' | COLOR_PAIR(gc.getColorId()+2));
				mvaddch(y+1, (2*x)+2, ' ' | COLOR_PAIR(gc.getColorId()+2));
				// mvaddch(y+1, (2*x)+1, ' ' | COLOR_PAIR(3));
				// mvaddch(y+1, (2*x)+2, ' ' | COLOR_PAIR(3));
			}
		}
	}
	refresh();
}


void define_pairs(){
	
	// const uint8_t colors[8] = {0, 197, 214, 226, 77, 81, 31, 133};
	const uint8_t colors[8] = {0, 197, 214, 226, 77, 81, 31, 133};
	
	for(uint8_t i=0; i<8; i++){
		init_pair(i+1, COLOR_WHITE, colors[i]);	//init_pair indexing seems to start at 1
	}
	/*<3*/
}


void print_colors() {
    for (int i = 0; i < 7; i++) {
        attron(COLOR_PAIR(i+ 1));  // Activer la couleur
    }
}



int ncurses_init(){
	
    initscr();
    cbreak();
    noecho();
    curs_set(0);

	if (has_colors() == FALSE) {
		endwin();
		perror("Le terminal ne supporte pas les couleurs.\n");
		return 1;
	}

    start_color();
	
	define_pairs();
}

void ncurses_quit(){
	endwin();
}
