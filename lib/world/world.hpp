#ifndef WORLD_WORLD_HPP
#define WORLD_WORLD_HPP

#include <string>
#include <vector>

namespace world {

  class World {
    enum CellType { FREE, SOLID, DESTROYABLE };

    size_t                width_;
    size_t                height_;
    std::vector<CellType> cells_;

  public:
    World(const std::string& filename);

    void RunMarchingSquares();
  };

}

#endif // WORLD_WORLD_HPP
