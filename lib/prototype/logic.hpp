#ifndef PROTOTYPE_LOGIC_HPP
#define PROTOTYPE_LOGIC_HPP

#include "event.hpp"
#include "world.hpp"


namespace prototype
{

  class Logic {

  public:

    Logic(EventQueue* e, World* w) : m_events(e), m_world(w) {}

  public:

    void step(double delta_time) {}

  private:
    EventQueue* m_events;
    World* m_world;
  };

}

#endif // PROTOTYPE_LOGIC_HPP
