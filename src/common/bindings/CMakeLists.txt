# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# BINDINGS source files
file(GLOB_RECURSE SOURCES_BINDINGS
    *.cpp
)
