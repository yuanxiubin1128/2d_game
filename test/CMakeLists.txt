# set(BUILD_TESTING_WITH_DEBUG CMAKE_BUILD_TYPE EQUAL "DEBUG" AND (TARGET EQUAL "cov" OR TARGET EQUAL "test")
# if (NOT BUILD_TESTING_WITH_DEBUG)
#     exit("cicaaaaa")
# endif (NOT BUILD_TESTING_WITH_DEBUG)

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

#if (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
#    exit("cicaaaaa nemdebug")
#    if (NOT ${TARGET} EQUAL "Debug")
#    exit("cicaaaaa nemdebug")
#endif (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")
#endif (NOT ${CMAKE_BUILD_TYPE} EQUAL "Debug")

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
  graph/test_graph.hpp

    cpp_utils/Fixture.hpp

  cpp_utils/test_Logger.hpp
  cpp_utils/test_ArgParse.hpp
  cpp_utils/test_Common.hpp
  cpp_utils/test_ConditionalVariable.hpp
  cpp_utils/test_Multiton.hpp
  cpp_utils/test_Mutex.hpp
  cpp_utils/test_ObjectPool.hpp
  cpp_utils/test_ScopedLock.hpp
  cpp_utils/test_Semaphore.hpp
#   cpp_utils/test_Singleton_DCLP.hpp
#   cpp_utils/test_Singleton_call_once.hpp
  # cpp_utils/test_Singleton.hpp Cannot test private member, Ficture.hpp loads it
#   cpp_utils/test_Singleton_meyers.hpp
  cpp_utils/test_Thread.hpp
  cpp_utils/test_ThreadPool.hpp

  cpp_utils/test_timerUser.hpp
  cpp_utils/test_Timer.hpp
  cpp_utils/test_Connection.hpp
  cpp_utils/test_StreamConnection.hpp
  cpp_utils/test_TcpConnection.hpp
  cpp_utils/test_Message.hpp
  )

  target_link_libraries(test_projectseed
                        subsystem_1
                        CppUtils
                        gcov)
endif()



add_custom_target( test
                   DEPENDS test_projectseed
)

add_custom_target( cov
                   COMMAND ./tools/run_test.sh ./test_projectseed
                   DEPENDS test_projectseed )
