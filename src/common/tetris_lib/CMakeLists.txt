# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# tetris_lib source files
file(GLOB_RECURSE SOURCES_TETRIS_LIB
    *.cpp
)

include(${CMAKE_SOURCE_DIR}/third_party/nlohmann.cmake)

# add tetris_lib as lib
add_library(tetris_lib STATIC ${SOURCES_TETRIS_LIB})

if(BUILD_STATIC)
    target_compile_options(tetris_lib PRIVATE -static-libstdc++ -static-libgcc)
    target_link_options(tetris_lib PRIVATE -static-libstdc++ -static-libgcc)
endif()

target_link_libraries(tetris_lib
  PUBLIC nlohmann_json::nlohmann_json
)

target_include_directories(tetris_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
