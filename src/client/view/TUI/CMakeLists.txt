cmake_minimum_required(VERSION 3.10)
project(TUI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ftxui REQUIRED)

add_executable(main main.cpp input/login_input.cpp login_menu/login_menu.cpp screen_manager.cpp main_menu/main_menu.cpp messaging/messaging.cpp game_display/game_display.cpp)

target_link_libraries(main PRIVATE ftxui::screen ftxui::dom ftxui::component)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(main PRIVATE 
        -Wall            
        -Wextra          
        -Wpedantic       
        -Wshadow         
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion    
        -Wsign-conversion 
        -Wmisleading-indentation
        -Wduplicated-cond
        -Wduplicated-branches 
        -Wlogical-op    
        -Wnull-dereference 
        -Wuseless-cast  
        -fstack-protector-strong
        -g              
    )
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(main PRIVATE DEBUG)
    message(STATUS "Compilation in Debug mod")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(main PRIVATE -O2 -DNDEBUG)
    message(STATUS "Compilation in Release mod")
endif()
