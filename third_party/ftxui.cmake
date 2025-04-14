find_package(ftxui 6.0.2 QUIET)
if (ftxui_FOUND)
  return()
endif()

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG 07fd3e685ade6275f718913720345134ed2e8242
  GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(ftxui)
