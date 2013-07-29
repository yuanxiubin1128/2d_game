#ifndef PROTOTYPE_WIDGET_HPP
#define PROTOTYPE_WIDGET_HPP

#include "event.hpp"
#include "world.hpp"

namespace prototype
{

  class Widget
  {
  public:

    void setEventQueue(EventQueue* events) { m_events = events; }
    void setWorldState(World* world) { m_world = world; }

    void render() {}

  private:
    EventQueue* m_events;
    World* m_world;
  };


}

#endif // PROTOTYPE_WIDGET_HPP
