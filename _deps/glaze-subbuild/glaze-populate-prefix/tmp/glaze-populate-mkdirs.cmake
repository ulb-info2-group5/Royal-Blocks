# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ernest/Info_f_209/group-5/_deps/glaze-src"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-build"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/tmp"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/src/glaze-populate-stamp"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/src"
  "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/src/glaze-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/src/glaze-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ernest/Info_f_209/group-5/_deps/glaze-subbuild/glaze-populate-prefix/src/glaze-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
