include(FetchContent)

FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG asio-1-28-0
)

FetchContent_MakeAvailable(asio)

if (TARGET asio)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(asio INTERFACE -Wno-deprecated-literal-operator)
    endif()
endif()
