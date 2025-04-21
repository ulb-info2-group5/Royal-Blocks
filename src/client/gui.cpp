#include "core/controller/controller.hpp"
#include "graphics/GUI/main_gui.hpp"

#include <iostream>
#include <memory>

int main(int argc, char *argv[]) {
    try {
        Controller controller(std::make_unique<GUI::MainGui>(argc, argv));
        controller.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
