include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(ftxui)
