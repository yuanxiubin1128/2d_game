#include "logic.hpp"

void prototype::Logic::modifyTrajectories()
{
  Event e;
  std::vector<Object>& objects = m_world->getObjectsRef();

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
  std::vector<Object>& objects = m_world->getObjectsRef();
  std::vector<Object>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it)
    adjustObject(*it, delta_time);
}

void prototype::Logic::adjustObject(Object& object, double delta_time)
{
  if (object.m_direction == 8)
    return;

  double speed = object.m_speed * delta_time;
  constexpr double sqtr_half = (double)1 / sqrt(2);
  double new_x = object.m_x;
  double new_y = object.m_y;

  switch (object.m_direction)
  {
    case 0: // North
      new_y -= speed; break;
    case 1: // NE
      new_y -= speed * sqtr_half; new_x += speed * sqtr_half; break;
    case 2: // East
      new_x += speed; break;
    case 3: // SE
      new_y += speed * sqtr_half; new_x += speed * sqtr_half; break;
    case 4: // South
      new_y += speed; break;
    case 5: // SW
      new_y += speed * sqtr_half; new_x -= speed * sqtr_half; break;
    case 6: // West
      new_x -= speed; break;
    case 7: // NW
      new_y -= speed * sqtr_half; new_x -= speed * sqtr_half; break;

    case 8: // none
    default:
      new_x = object.m_x; new_y = object.m_y;
  };

  object.m_x = (new_x < 0 || new_x > m_world->getWidth()) ? object.m_x : new_x;
  object.m_y = (new_y < 0 || new_x > m_world->getHeight()) ? object.m_y : new_y;
}
