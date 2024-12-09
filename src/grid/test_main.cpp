#include <ncurses.h>
#include <stdlib.h>

#include "../../include/grid/print_grid.hpp"

int main() {
    // Initialiser ncurses
    // initscr();
    // cbreak();
    // noecho();
    // curs_set(0);

	

    // Définir la taille de la grille
    
	// int rows = 20;
    // int cols = 10;

	// setenv("TERM", "xterm-256color", 1);

    // Vérifier si le terminal supporte les couleurs
    // if (has_colors() == FALSE) {
    //     endwin();
    //     perror("Le terminal ne supporte pas les couleurs.\n");
    //     return 1;
    // }

    // Initialiser le support des couleurs
    // start_color();

    // Définir les 6 couleurs distinctes
    // for (int i = 1; i <= 6; i++) {
    //     init_pair(i, i, COLOR_BLACK);  // Associer une couleur (1 à 6) à la couleur de fond noire
    // }

	
	// define_pairs();

    // draw_grid(rows, cols);// Appelle la fonction pour dessiner la grille
    // print_colors(); // Dessiner les chiffres avec les couleurs
    refresh(); // Actualiser l'écran
    getch(); // Attendre une touche pour quitter 
	// clear();
    endwin(); // Terminer ncurses

    return 0;
}
