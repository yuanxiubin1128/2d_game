#ifndef GAME_WORLD_HPP
#define GAME_WORLD_HPP

#include <string>
#include <vector>

namespace game {

  class World {
    enum CellType { FREE, SOLID, DESTROYABLE };

    size_t                width_;
    size_t                height_;
    std::vector<CellType> cells_;

  public:
    World(const std::string& filename);


  };

}

#endif // GAME_WORLD_HPP
