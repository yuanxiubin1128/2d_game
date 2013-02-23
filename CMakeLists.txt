cmake_minimum_required (VERSION 2.6)

project(graph)


set(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang")

set (CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++ -Wshadow "
               "-ggdb  -std=c++0x -D_GLIBCXX_PROFILE ")
add_definitions( ${CXX_FLAGS} )

# include_directories(.)

add_executable(graph main.cpp)
