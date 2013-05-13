#include <cxxtest/TestSuite.h>

#include <subsystem_1/dummy_class.hpp>

#include <iostream>

namespace test { class TestSubsystem1DummyClassSuite; }

class test::TestSubsystem1DummyClassSuite : public CxxTest::TestSuite
{

public:

  void testBasic()
  {
    subsystem_1::Dummy_class d;
    std::cout << "here" << std::endl;
    TS_ASSERT_EQUALS(1, 1);
  }

}; // class TestSubsystem1DummyClassSuite
