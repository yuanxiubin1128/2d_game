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

    void step(double delta_time) {
      modifyTrajectories();
      calculateNewPositions(delta_time);
    }

  private:
    void modifyTrajectories();
    void calculateNewPositions(double delta_time);
    void adjustObject(Object& object, double delta_time);

    EventQueue* m_events;
    World* m_world;
  };

} // namespace prototype


void prototype::Logic::modifyTrajectories()
{
  Event e;
  std::vector<Object> objects = m_world->getObjects();
  while (m_events->tryPop(e) == true) {
    std::vector<Object>::iterator it = std::find_if(objects.begin(), objects.end(),
                                                    [&e] (const Object& o)
                                                    { return o.m_id == e.m_id; });
    if (it == objects.end()) {
      // log error
      continue;
    }

    (*it).m_direction = e.m_direction;
    (*it).m_speed = e.m_speed;
  }
}

void prototype::Logic::calculateNewPositions(double delta_time)
{
  std::vector<Object> objects = m_world->getObjects();
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    adjustObject(*it, delta_time);
}

void prototype::Logic::adjustObject(Object& object, double delta_time)
{
  double speed = object.m_speed * delta_time;
  constexpr double sqtr_half = (double)1 / sqrt(2);
  double new_x = 0.0;
  double new_y = 0.0;

  switch (object.m_direction)
  {
    case 0: // North
      object.m_x -= speed; break;
    case 1: // NE
      object.m_x -= speed * sqtr_half; object.m_y += speed * sqtr_half; break;
    case 2: // East
      object.m_y += speed; break;
    case 3: // SE
      object.m_x += speed * sqtr_half; object.m_y += speed * sqtr_half; break;
    case 4: // South
      object.m_x += speed; break;
    case 5: // SW
      object.m_x += speed * sqtr_half; object.m_y -= speed * sqtr_half; break;
    case 6: // West
      object.m_y -= speed; break;
    case 7: // NW
      object.m_x -= speed * sqtr_half; object.m_y -= speed * sqtr_half; break;
    default:
      // log error
      break;
  };

  object.m_x = (new_x < 0 || new_x > m_world->getWidth()) ? object.m_x : new_x;
  object.m_y = (new_y < 0 || new_x > m_world->getHeight()) ? object.m_y : new_y;
}


#endif // PROTOTYPE_LOGIC_HPP
