#include "core/controller/controller.hpp"
#include <iostream>

#define BLANKLINE std::cout << std::endl;

/*
 * @brief Handle the arguments passed to the program
 *
 * @param argc The number of arguments
 * @param argv The arguments
 * @return The choice of the user interface
 */
UiChoice handleArguments(int argc, char *argv[]) {
    if (argc == 1) {
        std::cerr << "Tetris Royal : No arguments provided. See '" << argv[0]
                  << " --help' for more information." << std::endl;
    }

    else if (argc != 2) {

        std::cerr << "Tetris Royal : Invalid number of arguments. Expected one "
                     "argument. See '"
                  << argv[0] << " --help' for more information." << std::endl;
    }

    else if (std::string(argv[1]) == "--help") {
        std::cout << "Tetris Royal : Help" << std::endl;
        BLANKLINE;
        std::cout << "Usage: tetris_royal_client [OPTION]" << std::endl;
        BLANKLINE;
        std::cout << "Options:" << std::endl;
        std::cout << "  --help\t\tDisplay this information" << std::endl;
        std::cout
            << "  --gui\t\t\tStart the game with a graphical user interface"
            << std::endl;
        std::cout
            << "  --tui\t\t\tStart the game with a terminal user interface"
            << std::endl;
    }

    else if (std::string(argv[1]) == "--gui") {
        return UiChoice::GUI;
    }

    else if (std::string(argv[1]) == "--tui") {
        return UiChoice::TUI;
    }

    else {
        std::cerr << "Tetris Royal : '" << argv[1]
                  << "' is not a valid argument. See '" << argv[0]
                  << " --help' for more information." << std::endl;
    }

    return UiChoice::NONE;
}

int main(int argc, char *argv[]) {
    UiChoice choice = handleArguments(argc, argv);

    if (choice == UiChoice::NONE) {
        return 1;
    }

    Controller controller(choice);
    controller.run();
    return 0;
}
