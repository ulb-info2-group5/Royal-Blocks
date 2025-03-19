include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG 8519e9b0f31ac8f5765a3fc63c3b80a5cfbe9d6d
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(ftxui)
