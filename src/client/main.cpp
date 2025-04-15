#include "core/controller/controller.hpp"

#include <QApplication>
#include <iostream>

constexpr char noArgument[] = "\033[1;31merror:\033[0m no flag specified\nTry './tetris_royal_client --help' for more information.";
constexpr char invalidNumberOfArguments[] = "\033[1;31merror:\033[0m invalid number of arguments\nTry './tetris_royal_client --help' for more information.";
constexpr char invalidFlag []= "\033[1;31merror:\033[0m invalid flag specified\nTry './tetris_royal_client --help' for more information.";
constexpr char CHAR_TUI[] = "--tui";
constexpr char CHAR_GUI[] = "--gui";
constexpr char CHAR_HELP[] = "--help";
constexpr char helpInfo[] = "Tetris Royal : Help\n\nUsage: tetris_royal_client [OPTION]\n\nOptions:\n  --help\t\tDisplay this information\n  --gui\t\t\tStart the game with a graphical user interface\n  --tui\t\t\tStart the game with a terminal user interface";

/*
 * @brief Handle the arguments passed to the program
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return The choice of the user interface
 */
UiChoice handleArguments(int argc, char *argv[]) {
    if (argc == 1) {
        throw std::invalid_argument(noArgument);
    }

    else if (argc != 2) {
        throw std::invalid_argument(invalidNumberOfArguments);
    }

    else if (strcmp(argv[1], CHAR_GUI) == 0) {
        return UiChoice::GUI;
    }

    else if (strcmp(argv[1], CHAR_TUI) == 0) {
        return UiChoice::TUI;
    }

    else if (strcmp(argv[1], CHAR_HELP) == 0) {
        std::cout << helpInfo << std::endl;
        return UiChoice::NONE;
    }

    throw std::invalid_argument(invalidFlag);
}

int main(int argc, char *argv[]) {
    try {    
        UiChoice choice = UiChoice::GUI;
        if (choice == UiChoice::NONE) {
            return EXIT_SUCCESS;
        }
        Controller controller(choice, std::make_pair(argc, argv));
        return controller.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
