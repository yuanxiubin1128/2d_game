#ifndef PROTOTYPE_LOOP_HPP
#define PROTOTYPE_LOOP_HPP

#include "timer.hpp"
#include "logic.hpp"
#include "widget.hpp"

#include <cpp_utils/Thread.hpp>

#include <ctime>

namespace prototype
{

class Loop : public Thread
{
public:

  Loop(Logic* l, Widget* w) : m_timer(), m_logic(l), m_widget(w) {}

private:
  void* run() override
  {
    while(m_isRunning) {

      m_timer.registerStart();

      double dt = m_timer.getAvaregeDelta() / 1000000.0;
      const double fps = double(1) / dt;
      logEvery100thFps(fps);

      m_logic->step(dt);
      m_widget->render();

      slowDown(0.01); // gives me ~100fps on a 6core xeon

      m_timer.registerStop();
    }

    return 0;
  }

  void logEvery100thFps(double fps) const
  {
    static int i;
    ++i;
    if (i == 100) {
      m_widget->setFps(fps);
      i = 0;
    }
  }

  void slowDown(double s) const
  {
    const int nano = 1000000000;
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = s * nano;
    nanosleep(&ts, 0);
  }


  Timer<> m_timer;
  Logic* m_logic;
  Widget* m_widget;
};

}

#endif // PROTOTYPE_LOOP_HPP
