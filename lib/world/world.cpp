#include "world.hpp"

#include <png++/png.hpp>

using namespace game;

World::World(const std::string& filename) {
  png::image<png::gray_pixel> image(filename);

  width_  = image.get_width();
  height_ = image.get_height();
  cells_.reserve(width_ * height_);

  for (size_t y = 0; y < height_; ++y) {
    const png::image<png::gray_pixel>::row_type& row = image[y];
    for (size_t x = 0; x < width_; ++x) {
      CellType c; // map pixel luminance to cell type
      if (row[x] < 16)        c = SOLID;       // black
      else if (row[x] >= 240) c = FREE;        // white
      else                    c = DESTROYABLE; // everything else

      // mark borders as SOLID, such that the entities in the world cannot fall off
      if (x == 0 || x == width_ - 1 || y == 0 || height_ - 1)
        c = SOLID;

      cells_.push_back(c);
    }
  }
}
