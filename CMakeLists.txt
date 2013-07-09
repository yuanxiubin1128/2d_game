cmake_minimum_required (VERSION 2.6)
project (PROJECT_GRAPH)

set(CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Weffc++ -Wshadow --std=c++0x  -ggdb")
set(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++")

add_subdirectory (test)
