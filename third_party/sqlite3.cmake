include(ExternalProject)

find_program(MAKE_EXE NAMES gmake nmake make) # find make

ExternalProject_Add(sqlite3
  URL https://www.sqlite.org/2025/sqlite-autoconf-3490000.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  BUILD_IN_SOURCE true
  CONFIGURE_COMMAND ./configure --disable-shared # disable shared library
  BUILD_COMMAND     ${MAKE_EXE} all # build sqlite3 command
  INSTALL_COMMAND "" # Do not install sqlite3
)

# Make lsp's aware of libraries
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
