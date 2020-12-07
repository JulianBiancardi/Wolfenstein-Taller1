#include "map.h"

Map::Map(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

bool Map::is_free(size_t x,
                  size_t y,
                  Moveable &for_whom,
                  double movement_angle) {
  if (for_whom.collides_wall(x, y, movement_angle)) {
    return false;
  }
  return true;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}