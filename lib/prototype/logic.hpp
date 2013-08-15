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

    void step(float delta_seconds) { modifyTrajectories(); calculateNewPositions(delta_seconds); }

  private:
    void modifyTrajectories();
    void calculateNewPositions(float delta_seconds);
    void adjustObject(Object& object, float delta_seconds);

    EventQueue* m_events;
    World* m_world;
  };

} // namespace prototype

#endif // PROTOTYPE_LOGIC_HPP
