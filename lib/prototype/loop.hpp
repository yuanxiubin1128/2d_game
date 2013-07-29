#ifndef PROTOTYPE_LOOP_HPP
#define PROTOTYPE_LOOP_HPP

#include "timer.hpp"
#include "logic.hpp"
#include "widget.hpp"

#include <cpp_utils/Thread.hpp>

namespace prototype
{

class Loop : public Thread
{
public:

  Loop(Logic* l, Widget* w) : m_logic(l), m_widget(w) {}

private:
  void* run()
  {
    while(m_isRunning) {

      m_timer.registerStart();

      float dt = m_timer.getAvaregeDelta();
      m_logic->step(dt);

      m_widget->render();

      m_timer.registerStop();
    }

    return 0;
  }

  Timer m_timer;
  Logic* m_logic;
  Widget* m_widget;
};

}

#endif // PROTOTYPE_LOOP_HPP
