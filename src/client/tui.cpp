/*
 * This file is part of Royal Blocks.
 *
 * Royal Blocks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Royal Blocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Royal Blocks.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>                           
#include <exception>                          
#include <iostream>                           
#include <memory>               
              
#include "core/controller/controller.hpp"     
#include "graphics/TUI/main_tui.hpp"          
#include "graphics/common/abstract_display.hpp"

#include "version.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && (std::string(argv[1]) == "--version" || std::string(argv[1]) == "-v")) {
        std::cout << "royal-blocks version " << ROYAL_BLOCKS_VERSION << std::endl;
        return 0;
    }

    if (argc > 1 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        std::cout << "Usage: " << argv[0] << " [options]\n"
                << "\n"
                << "Just run the program to start it:\n"
                << "  " << argv[0] << "\n"
                << "\n"
                << "Options:\n"
                << "  -v, --version   Show version\n"
                << "  -h, --help      Show this help message\n";
        return 0;
    }


    try {
        Controller controller;
        controller.run(std::make_unique<TUI::MainTui>(controller));
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
