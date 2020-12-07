#include "map.h"

#define WALL 1  // TODO Try to move somewhere else

Map::Map(Matrix<int>& map_matrix) : map_matrix(map_matrix) {}

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}