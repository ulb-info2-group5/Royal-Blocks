# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# game_server lib
file(GLOB_RECURSE SOURCES_GAME_SERVER_LIB
    *.cpp
)

add_library(game_server_lib STATIC ${SOURCES_GAME_SERVER_LIB})

target_include_directories(game_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(${CMAKE_SOURCE_DIR}/third_party/asio.cmake)

target_link_libraries(game_server_lib PUBLIC
    tetris_royal_lib
)
