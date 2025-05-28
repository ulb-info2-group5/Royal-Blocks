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

if (WIN32)
    execute_process(
        COMMAND ${CMAKE_RC_COMPILER} -i ${CMAKE_SOURCE_DIR}/res/resource.rc -o ${CMAKE_BINARY_DIR}/resource.o
        RESULT_VARIABLE RC_RESULT
    )
    if (RC_RESULT EQUAL 0)
        set(RESOURCE_OBJ ${CMAKE_BINARY_DIR}/resource.o)
        target_sources(${PROJECT_NAME}-server PRIVATE ${RESOURCE_OBJ})
    else()
        message(FATAL_ERROR "Failed to compile resource")
    endif()
endif()
