#ifndef TOOLS_TEST_GLOBAL_FIXTURE_HPP
#define TOOLS_TEST_GLOBAL_FIXTURE_HPP

#include <cxxtest/TestSuite.h>
#include <cxxtest/GlobalFixture.h>

namespace test { class TestGlobalFixture; }

class test::TestGlobalFixture : public CxxTest::GlobalFixture
{
  bool setUpWorld()
  {
    /// @note Init before testing: logger, etc.
    return true;
  }

  bool tearDownWorld()
  {
    return true;
  }

};

static TestGlobalFixture testGlobalFixture;

#endif // TOOLS_TEST_GLOBAL_FIXTURE_HPP
