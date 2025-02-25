# client lib
file(GLOB_RECURSE SOURCES_CLIENT_LIB
    controller/*.cpp
    network/*.cpp
    view/*.cpp
)

add_library(client_lib STATIC ${SOURCES_CLIENT_LIB})

target_include_directories(client_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(../../third_party/ftxui.cmake)
find_package(Boost REQUIRED COMPONENTS system)

target_link_libraries(client_lib PRIVATE ftxui::screen ftxui::dom ftxui::component Boost::system)


# client binary
set(SOURCES_CLIENT_MAIN main.cpp)

add_executable(${PROJECT_NAME}_client ${SOURCES_CLIENT_MAIN})

target_link_libraries(${PROJECT_NAME}_client client_lib)


# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
