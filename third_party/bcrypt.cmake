include(FetchContent)

FetchContent_Declare(
  bcrypt
  GIT_REPOSITORY https://github.com/hilch/Bcrypt.cpp.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(bcrypt)