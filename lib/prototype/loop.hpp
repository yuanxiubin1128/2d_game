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

  typedef Timer<std::chrono::microseconds> MicrosecondsTimer;
  typedef std::chrono::duration<float> sec;

  void* run() override
  {
    constexpr MicrosecondsTimer::Duration fixedTimeSlice = std::chrono::microseconds(16*1000);
    constexpr sec fixedTimeSliceInSec = std::chrono::duration_cast<sec>(fixedTimeSlice);

    MicrosecondsTimer::TimePoint simulationTime = m_timer.getTime();
    MicrosecondsTimer::TimePoint realTime;

    while(m_isRunning) {

      realTime = m_timer.getTime();
      m_timer.registerStart(realTime);

      while (simulationTime < realTime){
        simulationTime += fixedTimeSlice;
        m_logic->step(fixedTimeSliceInSec.count());
      }

      m_widget->render();
      nanoSleep();

      MicrosecondsTimer::Duration delta(static_cast<MicrosecondsTimer::RepT>(m_timer.getAvaregeDelta()));
      logFpsEverySecond(1.0 /std::chrono::duration_cast<sec>(delta).count());

      m_timer.registerStop();
    }

    return 0;
  }

  void logFpsEverySecond(float fps) const
  {
    static MicrosecondsTimer::TimePoint lastLog;
    MicrosecondsTimer::TimePoint now = m_timer.getTime();
    std::chrono::duration<float> elapsed_time = now - lastLog;
    if (elapsed_time.count() > 1.0) {
      m_widget->setFps(fps);
      lastLog = now;
    }
  }

  void nanoSleep(int64_t nanoSeconds = 1000000) const
  {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = nanoSeconds;
    nanosleep(&ts, 0);
  }


  MicrosecondsTimer m_timer;
  Logic* m_logic;
  Widget* m_widget;
};

}

#endif // PROTOTYPE_LOOP_HPP
