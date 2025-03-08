# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)


# network lib
file(GLOB_RECURSE SOURCES_NETWORK_LIB
    *.cpp
)

add_library(network_lib STATIC ${SOURCES_NETWORK_LIB})

target_include_directories(network_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(network_lib PUBLIC
    Boost::system
    game_server_lib
    database_lib
)


# TODO: remove this (temporary)
# network binary
set(SOURCES_NETWORK_MAIN main.cpp)
add_executable(network ${SOURCES_NETWORK_MAIN})
target_link_libraries(network network_lib)
