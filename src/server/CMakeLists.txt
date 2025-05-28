# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

file(GLOB_RECURSE SERVER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

include(${CMAKE_SOURCE_DIR}/third_party/asio.cmake)

add_library(server_lib STATIC ${SERVER_SOURCES})
add_subdirectory(database)

target_include_directories(server_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(server_lib PUBLIC
    bcrypt
    tetris_royal_lib
    database_lib
    asio
)

if(WIN32)
    target_link_libraries(server_lib PUBLIC ws2_32 mswsock)
endif()


set(SOURCE_SERVER_MAIN main.cpp)
add_executable(${PROJECT_NAME}-server ${SOURCE_SERVER_MAIN})

target_link_libraries(${PROJECT_NAME}-server server_lib)
