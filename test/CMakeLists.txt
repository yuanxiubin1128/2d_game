find_package(CxxTest)
if(CXXTEST_FOUND)

  include_directories(${CXXTEST_INCLUDE_DIR}
                      ../lib)

  enable_testing()

  CXXTEST_ADD_TEST(test_graph
                   generated_main.cpp
                   graph/test_graph.hpp)

endif()

add_custom_target( test
                   COMMAND ./test_graph
)