#include "base_map.h"

#define WALL 1  // TODO Remove this and ask in Config

BaseMap::BaseMap(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

BaseMap::~BaseMap() {}

bool BaseMap::is_wall(size_t x, size_t y) {
  if ((x < 0) || (y < 0)
      || (x>=map_matrix.get_columns()) || (y>=map_matrix.get_rows()))
    return false; //TODO check if neccesary

  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

int BaseMap::operator()(size_t x, size_t y) { return map_matrix(x, y); }
