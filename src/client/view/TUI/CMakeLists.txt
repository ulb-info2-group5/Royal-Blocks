cmake_minimum_required(VERSION 3.10)
project(TUI)

# Utilisation de C++ 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recherche FTXUI avec pkg-config
find_package(ftxui REQUIRED)

# Ajout des fichiers sources
add_executable(main main.cpp input/login_input.cpp login_menu/login_menu.cpp tui_manager.cpp)

# Ajout des options de compilation
target_link_libraries(main PRIVATE ftxui::screen ftxui::dom ftxui::component)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

