# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# database_lib source files
file(GLOB_RECURSE SOURCES_DATABASE_LIB
    *.cpp
)

# dependencies
include(${CMAKE_SOURCE_DIR}/third_party/nlohmann.cmake)

# add database_lib as lib
add_library(database_lib STATIC ${SOURCES_DATABASE_LIB})

# link against dependencies
target_include_directories(database_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(database_lib
  PUBLIC nlohmann_json::nlohmann_json
  PUBLIC sqlite3
)
