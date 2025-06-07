# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# tetris_royal_lib source files
file(GLOB_RECURSE SOURCES_TETRIS_ROYAL_LIB
    *.cpp
)

# add tetris_royal_lib as lib
add_library(tetris_royal_lib STATIC ${SOURCES_TETRIS_ROYAL_LIB})

if(BUILD_STATIC)
    target_compile_options(tetris_royal_lib PRIVATE -static-libstdc++ -static-libgcc)
    target_link_options(tetris_royal_lib PRIVATE -static-libstdc++ -static-libgcc)
endif()


target_include_directories(tetris_royal_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# link against tetris_lib (dependency)
target_link_libraries(tetris_royal_lib PUBLIC tetris_lib)
