# cmake -DCMAKE_BUILD_TYPE=Release .
# cmake -DCMAKE_BUILD_TYPE=Debug .

# The following targets are available:
# make
# make test
# make coverage
# make doc

# TODO ensure that CMAKE_BUILD_TYPE=Debug before test or cov targets

cmake_minimum_required (VERSION 2.6)
project (PROJECT_SEED)

set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Weffc++ -Wshadow --std=c++0x ")

set(CMAKE_CXX_FLAGS_DEBUG " ${CMAKE_CXX_FLAGS} -ggdb -fprofile-arcs -ftest-coverage ")
set(CMAKE_CSS_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS} ")

set(CMAKE_CXX_COMPILER "clang++")

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()


add_subdirectory (lib)
# add_subdirectory (build)
add_subdirectory (test EXCLUDE_FROM_ALL)
