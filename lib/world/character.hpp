#ifndef WORLD_CHARACTER_HPP
#define WORLD_CHARACTER_HPP

#include "entity.hpp"

namespace world {

  class Character : public Entity {
    
  public:
    
  };

  struct CharacterInput {
    float2 move_; // x=west/east, y=south/north: [-1;+1]
    float  turn_; // left/right: [-1;+1]
    bool   shoot_; 
  };
}

#endif // WORLD_CHARACTER_HPP

