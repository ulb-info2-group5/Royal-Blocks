# Add bcrypt (compiled from source)
add_subdirectory(Bcrypt.cpp)

# Add SQLite as a static library from source
add_library(sqlite3 STATIC sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sqlite)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sqlite3 PRIVATE -Wno-stringop-overread)
endif()

# Add asio as a static library from source
add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/asio/include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(asio INTERFACE -Wno-deprecated-literal-operator)
endif()
