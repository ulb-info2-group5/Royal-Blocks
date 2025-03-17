# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# client lib
file(GLOB_RECURSE SOURCES_CLIENT_LIB
    *.cpp
)

add_library(client_lib STATIC ${SOURCES_CLIENT_LIB})

target_include_directories(client_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)

include(../../third_party/ftxui.cmake)
find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(client_lib PUBLIC
    ftxui::screen
    ftxui::dom
    ftxui::component
    Boost::system
    tetris_royal_lib
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
)


# client binary
set(SOURCES_CLIENT_MAIN main.cpp)

add_executable(${PROJECT_NAME}_client ${SOURCES_CLIENT_MAIN})

target_link_libraries(${PROJECT_NAME}_client client_lib)

