#ifndef PROTOTYPE_LOGIC_HPP
#define PROTOTYPE_LOGIC_HPP

#include "event.hpp"
#include "world.hpp"

namespace prototype
{

  class Logic {


  public:

    void setEventQueue(EventQueue* events) { m_events = events; }
    void setWorldState(World* world) { m_world = world; }

    void step(float delta_time) {}

  private:
    EventQueue* m_events;
    World* m_world;
  };

}

#endif // PROTOTYPE_LOGIC_HPP
