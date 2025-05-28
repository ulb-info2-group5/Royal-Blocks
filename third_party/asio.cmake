include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/boostorg/asio.git
    GIT_TAG        boost-1.84.0
)

FetchContent_MakeAvailable(asio)
