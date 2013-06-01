#ifndef GAME_ENTITY_HPP
#define GAME_ENTITY_HPP

#include "floats.hpp"

namespace game {

  class Entity {
    float2 position_;    // x=west/east, y=south/north
    float2 velocity_;    // x=west/east, y=south/north
    float  orientation_; // radians, 0.0 faces north
    
  public:
    
  };

}

#endif // GAME_ENTITY_HPP

