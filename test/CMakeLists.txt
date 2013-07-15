
# set(BUILD_TESTING_WITH_DEBUG CMAKE_BUILD_TYPE EQUAL "DEBUG" AND (TARGET EQUAL "cov" OR TARGET EQUAL "test")
# if (NOT BUILD_TESTING_WITH_DEBUG)
#     exit("cicaaaaa")
# endif (NOT BUILD_TESTING_WITH_DEBUG)

# set(BUILD_TESTING_WITH_DEBUG CMAKE_BUILD_TYPE EQUAL "DEBUG" AND (TARGET EQUAL "cov" OR TARGET EQUAL "test")
# if (CMAKE_BUILD_TYPE EQUAL "Debu")
#     message("DENES DEBUG")
# endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")
# message("cicc ${CMAKE_BUILD_TYPE}")
# message("cicc2 ${TARGET}")

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

if (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
    exit("cicaaaaa nemdebug")
    if (NOT ${TARGET} EQUAL "Debug")
    exit("cicaaaaa nemdebug")
endif (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
endif (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")

find_package(CxxTest)
if(CXXTEST_FOUND)

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
