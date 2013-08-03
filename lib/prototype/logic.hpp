#ifndef PROTOTYPE_LOGIC_HPP
#define PROTOTYPE_LOGIC_HPP

#include "event.hpp"
#include "world.hpp"

#include <algorithm>
#include <cmath>

namespace prototype
{

  class Logic {

  public:

    Logic(EventQueue* e, World* w) : m_events(e), m_world(w) {}

  public:

    void step(double delta_time) { modifyTrajectories(); calculateNewPositions(delta_time); }

  private:
    void modifyTrajectories();
    void calculateNewPositions(double delta_time);
    void adjustObject(Object& object, double delta_time);

    EventQueue* m_events;
    World* m_world;
  };

} // namespace prototype

#endif // PROTOTYPE_LOGIC_HPP
