# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


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


# ---------------------------
#            TUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_TUI
    graphics/common/*.cpp
    graphics/TUI/*.cpp
    tui.cpp
)

include(../../third_party/ftxui.cmake)

add_executable(royal-blocks-tui ${SOURCES_CLIENT_TUI})

target_link_libraries(royal-blocks-tui
    client_core_lib
    ftxui::screen
    ftxui::dom
    ftxui::component
)

if(WIN32)
    target_link_libraries(royal-blocks-tui ws2_32)
endif()


# ---------------------------
#            GUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_GUI
    graphics/common/*.cpp
    graphics/GUI/*.cpp
    gui.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)


add_executable(royal-blocks-gui ${SOURCES_CLIENT_GUI})

if (WIN32)
    target_link_options(royal-blocks-gui PRIVATE -mwindows)
endif()

# AUTOMOC only needed for Qt5 for the GUI
set_target_properties(royal-blocks-gui PROPERTIES AUTOMOC ON )

target_link_libraries(royal-blocks-gui
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    client_core_lib
)

if(WIN32)
    target_link_libraries(royal-blocks-gui ws2_32)
endif()

