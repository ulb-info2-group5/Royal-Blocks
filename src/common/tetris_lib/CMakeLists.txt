# tetris_lib source files
file(GLOB_RECURSE SOURCES_TETRIS_LIB
    *.cpp
)


# Make lsp's aware of our libraries (make includes work basically)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# add tetris_lib as lib
add_library(tetris_lib STATIC ${SOURCES_TETRIS_LIB})

target_include_directories(tetris_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
