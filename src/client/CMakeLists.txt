# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ---------------------------
#         Client Core
# ---------------------------

# client lib
file(GLOB_RECURSE SOURCES_CLIENT_CORE_LIB
    core/*.cpp
)

add_library(client_core_lib STATIC ${SOURCES_CLIENT_CORE_LIB})
target_link_libraries(client_core_lib PUBLIC tetris_royal_lib)
target_include_directories(client_core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# TODO: NOT SURE THIS IS REQUIRED
find_package(Boost CONFIG)


# ---------------------------
#            TUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_TUI
    graphics/common/*.cpp
    graphics/TUI/*.cpp
    tui.cpp
)

include(../../third_party/ftxui.cmake)

add_executable(tetris_tui ${SOURCES_CLIENT_TUI})
target_link_libraries(tetris_tui
    client_core_lib
    ftxui::screen
    ftxui::dom
    ftxui::component
)

# ---------------------------
#            GUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_GUI
    graphics/common/*.cpp
    graphics/GUI/*.cpp
    gui.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(tetris_gui ${SOURCES_CLIENT_GUI})
target_link_libraries(tetris_gui
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    client_core_lib
)
