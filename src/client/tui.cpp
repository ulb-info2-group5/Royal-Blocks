#include "core/controller/controller.hpp"
#include "graphics/TUI/main_tui.hpp"

#include <iostream>
#include <memory>

int main(void) {
    try {
        Controller controller;
        controller.run(std::make_unique<TUI::MainTui>(controller));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
