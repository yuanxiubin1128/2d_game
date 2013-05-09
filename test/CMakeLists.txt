# set(CMAKE_CXX_COMPILER "/usr/lib/colorgcc/bin/g++")

# NOTE testing compiler flags may differ from release flags: debug info, etc
set (CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++ -Wshadow "
               "-Wpointer-arith -Wcast-qual "
               "-ggdb -fprofile-arcs -ftest-coverage --std=c++0x " )

add_definitions( ${CXX_FLAGS} )


find_package(CxxTest)
if(CXXTEST_FOUND)

#   set(CXXTEST_USE_PERL TRUE)
  include_directories(${CXXTEST_INCLUDE_DIR}
                      ../lib)

  enable_testing()

  CXXTEST_ADD_TEST(
  test_projectseed
  generated_main.cpp
  ./tools/TestGlobalFixture.hpp

  subsystem_1_tests/test_dummy_class.hpp
  )

  target_link_libraries(test_projectseed
                        subsystem_1
                        gcov)
endif()


add_custom_target( test
                   DEPENDS test_projectseed
)

add_custom_target( cov
                   COMMAND ./tools/run_test.sh ./test_projectseed
                   DEPENDS test_projectseed
)
