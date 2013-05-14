cmake_minimum_required (VERSION 2.6)

project(graph)


set(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++")
# set(CMAKE_CXX_COMPILER "/usr/bin/clang")

set (CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++ -Wshadow -ggdb  -std=c++0x")
add_definitions( ${CXX_FLAGS} )


find_package(CxxTest)
if(CXXTEST_FOUND)

  include_directories(${CXXTEST_INCLUDE_DIR}
                      ../lib)

  enable_testing()

  CXXTEST_ADD_TEST(
  test_graph
  generated_main.cpp

  test_graph.hpp
  )

endif()
