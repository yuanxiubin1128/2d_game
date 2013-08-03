#ifndef PROTOTYPE_OBJECT_HPP
#define PROTOTYPE_OBJECT_HPP

#include <string>

namespace prototype
{

  class Object
  {
  public:

    Object(const std::string id, int direction, float speed, float x, float y)
      : m_id(id), m_direction(direction), m_speed(speed), m_x(x), m_y(y) {}

    std::string m_id; // IP

    // 0-7 enumerating directions starting from top going clockwise.
    // 0 - North, 1 - NE, 2, East, ...
    int m_direction;

    float m_speed; // 0 or constant, pixel / second
    int m_x, m_y; // Position
  };

}

#endif // PROTOTYPE_OBJECT_HPP
