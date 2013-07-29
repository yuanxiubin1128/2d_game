#ifndef PROTOYPE_TIMIR_HPP
#define PROTOYPE_TIMIR_HPP

#include <queue>

namespace prototype
{

  class Timer
  {

  public:
    void registerStart() {}
    void registerStop() {}

    float getAvaregeDelta() const { return 0.0; }

  private:
    int m_time;
    std::queue<float> m_diffs;
  };

}

#endif // PROTOYPE_TIMIR_HPP

