# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# database_lib source files
file(GLOB_RECURSE SOURCES_DATABASE_LIB
    *.cpp
)

# dependencies
include(../../../third_party/sqlite3.cmake)
include(../../../third_party/glaze.cmake)

# add database_lib as lib
add_library(database_lib STATIC ${SOURCES_DATABASE_LIB})

# link against dependencies
add_dependencies(database_lib sqlite3)
ExternalProject_Get_property(sqlite3 SOURCE_DIR)
target_include_directories(database_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(database_lib
  PUBLIC glaze::glaze
  PUBLIC "${SOURCE_DIR}/libsqlite3.a"
)
