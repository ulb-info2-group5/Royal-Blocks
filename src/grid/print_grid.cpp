
#include <ncurses.h>

#include "../board/board.hpp"
#include "../board/grid_cell.hpp"

void draw_grid(int rows, int cols) {

    clear();

    for (uint32_t y = 0; y < rows; y++) {
        mvaddch(y + 1, 0, '|');
        mvaddch(y + 1, 2 * (cols + 1) - 1, '|');
    }
    for (uint32_t x = 0; x < 2 * cols; x++) {
        mvaddch(0, x + 1, '-');
        mvaddch(rows + 2 - 1, x + 1, '-');
    }
    /*<3*/

    mvaddch(0, 0, '+');
    mvaddch(0, (cols * 2) + 1, '+');
    mvaddch((rows + 1), 0, '+');
    mvaddch((rows + 1), (cols * 2) + 1, '+');
    /*<3*/

    // refresh();
}

void draw_cells(Board *board) {
    uint32_t height = board->getHeight();
    uint32_t width = board->getWidth();
    GridCell gc;
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            gc = board->get(y, x);
            // printf("isEmpty ? : %1x\n", gc.isEmpty());
            if (!gc.isEmpty()) {
                // mvaddch(x+1, y+1, ' ' | COLOR_PAIR(gc.getColorId()));
                mvaddch(y + 1, (2 * x) + 1,
                        ' ' | COLOR_PAIR(gc.getColorId() + 2));
                mvaddch(y + 1, (2 * x) + 2,
                        ' ' | COLOR_PAIR(gc.getColorId() + 2));
                // mvaddch(y+1, (2*x)+1, ' ' | COLOR_PAIR(3));
                // mvaddch(y+1, (2*x)+2, ' ' | COLOR_PAIR(3));
            }
        }
    }
    // refresh();
}

void draw_active(Tetromino *activeTetromino) {

    const Coordinate anchor = activeTetromino->getAnchorPoint();

    for (const Coordinate &relativeCoord : activeTetromino->getBody()) {
        Coordinate absoluteCoord = anchor + relativeCoord;
        uint32_t x = absoluteCoord.getCol();
        uint32_t y = absoluteCoord.getRow();
        mvaddch(y + 1, (2 * x) + 1,
                ' ' | COLOR_PAIR(activeTetromino->getColorId() + 2));
        mvaddch(y + 1, (2 * x) + 2,
                ' ' | COLOR_PAIR(activeTetromino->getColorId() + 2));
    }

    // refresh();
}

void draw_preview(Tetromino *previewTetromino) {	//same code as draw_active for now but future iterations might deffer

	const Coordinate anchor = previewTetromino->getAnchorPoint();

    for (const Coordinate &relativeCoord : previewTetromino->getBody()) {
        Coordinate absoluteCoord = anchor + relativeCoord;
        uint32_t x = absoluteCoord.getCol();
        uint32_t y = absoluteCoord.getRow();
        mvaddch(y + 1, (2 * x) + 1,
                ' ' | COLOR_PAIR(9));	//preview color : see define_pairs()
        mvaddch(y + 1, (2 * x) + 2,
                ' ' | COLOR_PAIR(9));

    }

    // refresh();

}

void print_debug(char *str, uint32_t gridWidth) {

    uint32_t i = 0;
    uint32_t messageWidth = 16;

    while (str[i] != 0x00) {

        if (str[i] != '\n')
            mvaddch(1 + (i / messageWidth),
                    ((gridWidth + 2) * 2) + (i % messageWidth), str[i]);
        else i += messageWidth - (i % messageWidth) - 1;
        i++;
    }

    // refresh();
}


void print_score(size_t score, uint32_t gridWidth){
	
	size_t current = score;
	uint32_t lineWidth = 16;	//in case you get like 10e16< score
	uint32_t i = 0;

	while((score!=0) || (i==0)){
		mvaddch(1 + (i / lineWidth) + 1, ((gridWidth + 2) * 2) + (i % lineWidth), '0'+(score%10));
		score/=10;
		i++;
	}
}

void ncurses_refresh(){		//not the prettiest but tetris.cpp won't need ncurses.h
	refresh();
}

void define_pairs() {

    // const uint8_t colors[8] = {0, 197, 214, 226, 77, 81, 31, 133};
    const uint8_t colors[8] = {0, 197, 214, 226, 77, 81, 31, 133};

    for (uint8_t i = 0; i < 8; i++) {
        init_pair(i + 1, COLOR_WHITE,
                  colors[i]); // init_pair indexing seems to start at 1
    }

	init_pair(9, COLOR_WHITE, 236);	//grey for the preview tetromino
    /*<3*/
}

void print_colors() {
    for (int i = 0; i < 7; i++) {
        attron(COLOR_PAIR(i + 1)); // Activer la couleur
    }
}

int ncurses_init() {
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
    return 0;
}

void ncurses_quit() { endwin(); }
