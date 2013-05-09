cmake_minimum_required (VERSION 2.6)
project (PROJECT_SEED)

add_subdirectory (lib)
add_subdirectory (build)
add_subdirectory (test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile)
endif(DOXYGEN_FOUND)
