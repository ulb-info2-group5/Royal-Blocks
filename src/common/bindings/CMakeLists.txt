# tetris_lib source files
file(GLOB_RECURSE SOURCES_BINDINGS
    *.cpp
)

include(../../../third_party/nlohmann.cmake)

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
