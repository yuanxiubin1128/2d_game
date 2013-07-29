#ifndef PROTOTYPE_OBJECT_HPP
#define PROTOTYPE_OBJECT_HPP

#include <string>

namespace prototype
{

  class Object
  {
  public:


  private:

    std::string m_id; // IP
    int m_direction; // 0-7 enumerating directions starting from top going clockwise.
    float m_speed; // 0 or constant, pixel / second
    int m_x, m_y; // Position
  };

}

#endif // PROTOTYPE_OBJECT_HPP
