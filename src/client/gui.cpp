#include <stdlib.h>                            
#include <exception>                           
#include <iostream>                            
#include <memory>             
                 
#include "core/controller/controller.hpp"      
#include "graphics/GUI/main_gui.hpp"           
#include "graphics/common/abstract_display.hpp"

int main(int argc, char *argv[]) {
    try {
        Controller controller;
        controller.run(std::make_unique<GUI::MainGui>(controller, argc, argv));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
