# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# network lib
file(GLOB_RECURSE SERVER_SOURCES
    *.cpp
)

add_library(server_lib STATIC ${SERVER_SOURCES})


target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(../../third_party/nlohmann.cmake)
find_package (SQLite3)
find_package(Boost CONFIG)

target_link_libraries(server_lib PUBLIC
    bcrypt
    tetris_royal_lib
    PUBLIC nlohmann_json::nlohmann_json
    PUBLIC sqlite3
)


set(SOURCE_SERVER_MAIN main.cpp)
add_executable(${PROJECT_NAME}_server ${SOURCE_SERVER_MAIN})
target_link_libraries(${PROJECT_NAME}_server server_lib)
