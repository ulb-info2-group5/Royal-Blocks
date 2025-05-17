# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE SERVER_SOURCES
    client_link/*.cpp
    client_manager/*.cpp
    network/*.cpp
    server_bindings/*.cpp
    social_service/*.cpp
    games_manager/*.cpp
    game_server/*.cpp
    matchmaking/*.cpp
    account_service/*.cpp
    tetris_main_server/*.cpp
)

add_library(server_lib STATIC ${SERVER_SOURCES})
add_subdirectory(database)

target_include_directories(server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_link_libraries(server_lib PUBLIC
    bcrypt
    tetris_royal_lib
    database_lib
)

if(WIN32)
    target_link_libraries(server_lib PUBLIC ws2_32 mswsock)
endif()


set(SOURCE_SERVER_MAIN main.cpp)
add_executable(${PROJECT_NAME}-server ${SOURCE_SERVER_MAIN})

target_link_libraries(${PROJECT_NAME}-server server_lib)
