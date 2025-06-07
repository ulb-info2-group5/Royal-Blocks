# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

# ---------------------------
#         Client Core
# ---------------------------

include(${CMAKE_SOURCE_DIR}/third_party/asio.cmake)

# client lib
file(GLOB_RECURSE SOURCES_CLIENT_CORE_LIB
    core/*.cpp
)

add_library(client_core_lib STATIC ${SOURCES_CLIENT_CORE_LIB})
target_link_libraries(client_core_lib PUBLIC tetris_royal_lib asio)
target_include_directories(client_core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---------------------------
#            TUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_TUI
    graphics/common/*.cpp
    graphics/TUI/*.cpp
    tui.cpp
)

set(BUILD_SHARED_LIBS OFF)
include(${CMAKE_SOURCE_DIR}/third_party/ftxui.cmake)

add_executable(${PROJECT_NAME}-tui ${SOURCES_CLIENT_TUI})

if(BUILD_STATIC)
    target_compile_options(${PROJECT_NAME}-tui PRIVATE -static-libstdc++ -static-libgcc)
    target_link_options(${PROJECT_NAME}-tui PRIVATE -static-libstdc++ -static-libgcc)
endif()

target_link_libraries(${PROJECT_NAME}-tui PRIVATE
    client_core_lib
    ftxui::screen
    ftxui::dom
    ftxui::component
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}-tui ws2_32)
endif()


# ---------------------------
#            GUI
# ---------------------------

file (GLOB_RECURSE SOURCES_CLIENT_GUI
    graphics/common/*.cpp
    graphics/GUI/*.cpp
    gui.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui)


add_executable(${PROJECT_NAME}-gui ${SOURCES_CLIENT_GUI})

if (WIN32)
    target_link_options(${PROJECT_NAME}-gui PRIVATE -mwindows)
endif()

if(BUILD_STATIC)
    target_compile_options(${PROJECT_NAME}-gui PRIVATE -static-libstdc++ -static-libgcc)
    target_link_options(${PROJECT_NAME}-gui PRIVATE -static-libstdc++ -static-libgcc)
endif()

# AUTOMOC only needed for Qt5 for the GUI
set_target_properties(${PROJECT_NAME}-gui PROPERTIES AUTOMOC ON )

target_link_libraries(${PROJECT_NAME}-gui PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    client_core_lib
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}-gui ws2_32)
endif()

if (WIN32)
    execute_process(
        COMMAND ${CMAKE_RC_COMPILER} -i ${CMAKE_SOURCE_DIR}/res/resource.rc -o ${CMAKE_BINARY_DIR}/resource.o
        RESULT_VARIABLE RC_RESULT
    )
    if (RC_RESULT EQUAL 0)
        set(RESOURCE_OBJ ${CMAKE_BINARY_DIR}/resource.o)
        target_sources(${PROJECT_NAME}-tui PRIVATE ${RESOURCE_OBJ})
        target_sources(${PROJECT_NAME}-gui PRIVATE ${RESOURCE_OBJ})
    else()
        message(FATAL_ERROR "Failed to compile resource")
    endif()
endif()
