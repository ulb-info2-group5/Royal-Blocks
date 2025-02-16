# tetris_lib source files
file(GLOB_RECURSE SOURCES_TETRIS_LIB
    *.cpp
)

include(../../../third_party/glaze.cmake)

# add tetris_lib as lib
add_library(tetris_lib STATIC ${SOURCES_TETRIS_LIB})

target_link_libraries(tetris_lib
  PUBLIC glaze::glaze
)

target_include_directories(tetris_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
