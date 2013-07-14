find_package(CxxTest)
if(CXXTEST_FOUND)

  include_directories(${CXXTEST_INCLUDE_DIR}
                      ../lib)

  enable_testing()

  CXXTEST_ADD_TEST(test_projectseed
                   generated_main.cpp
                   ./tools/TestGlobalFixture.hpp

                   # add test:
                   subsystem_1_tests/test_dummy_class.hpp
                   graph/test_graph.hpp
                   )

  target_link_libraries(test_projectseed

                        # add subsystem libs:
                        subsystem_1

                        # system libs:
                        gcov)
endif()


# test is excluded from the default build
add_custom_target( test
                   DEPENDS test_projectseed
)

add_custom_target( cov
                   COMMAND ./tools/run_test.sh ./test_projectseed
                   DEPENDS test_projectseed
)
