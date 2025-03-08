# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# game_server lib
file(GLOB_RECURSE SOURCES_GAME_SERVER_LIB
    *.cpp
)

add_library(game_server_lib STATIC ${SOURCES_GAME_SERVER_LIB})

target_include_directories(game_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(game_server_lib PUBLIC
    Boost::system
    tetris_royal_lib
)


# TODO: remove this (temporary)
# game_server binary
set(SOURCES_GAME_SERVER_MAIN main.cpp)
add_executable(game_server ${SOURCES_GAME_SERVER_MAIN})

target_link_libraries(game_server game_server_lib)
