#ifndef PROTOTYPE_EVENT_HPP
#define PROTOTYPE_EVENT_HPP

#include <cpp_utils/ConcurrentDeque.hpp>

#include <string>

namespace prototype
{

  class Event {
  public:
    std::string m_id; // IP
    int m_direction; // 0-7 enumerating directions starting from top going clockwise.
    float m_speed; // 0 or constant, pixel / second
  };

  typedef ConcurrentDeque<Event> EventQueue;

}

#endif // PROTOTYPE_EVENT_HPP

