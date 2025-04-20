#include "core/controller/controller.hpp"
#include "graphics/GUI/main_gui.hpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    try {

        QApplication app(argc, argv);

        app.setApplicationName("Royal Tetris");
        app.setApplicationDisplayName("Royal Tetris");

        Controller controller(std::make_unique<GUI::MainGui>(app));
        controller.run();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
