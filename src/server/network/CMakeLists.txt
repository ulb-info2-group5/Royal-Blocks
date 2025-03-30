# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# network lib
file(GLOB_RECURSE SOURCES_NETWORK_LIB
    *.cpp
)

add_library(network_lib STATIC ${SOURCES_NETWORK_LIB})

target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost CONFIG)

target_link_libraries(network_lib PUBLIC
    game_server_lib
    database_lib
    bcrypt
)


set(SOURCE_SERVER_MAIN main.cpp)
add_executable(${PROJECT_NAME}_server ${SOURCE_SERVER_MAIN})
target_link_libraries(${PROJECT_NAME}_server network_lib)
