#ifndef PROTOTYPE_WORLD_HPP
#define PROTOTYPE_WORLD_HPP

#include "object.hpp"

#include <vector>

// Possible Mutex ?

namespace prototype
{

  class World
  {

  public:

    World() : m_height(0), m_width(0), m_objects() {}

    World(const World&) = delete;
    World(World&&) = delete;
    World& operator=(const World&) = delete;

    void setHeight(float h) { m_height = h; }
    float getHeight() const { return m_height; }

    void setWidth(float w) { m_width = w; }
    float getWidth() const { return m_width; }

    void addObject(const Object& o) { m_objects.push_back(o); }
    std::vector<Object>& getObjectsRef() { return m_objects; }

  private:

    float m_height;
    float m_width;
    std::vector<Object> m_objects;
  };

}

#endif // PROTOTYPE_WORLD_HPP
