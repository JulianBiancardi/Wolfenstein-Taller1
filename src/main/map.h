#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include <matrix.h>

class Map {
 private:
  Matrix<int> map_matrix;

 public:
  Map(Matrix<int> map_matrix);
  bool is_wall(size_t x, size_t y);
  ~Map();
};

#endif

Map::Map(Matrix<int> map_matrix) : map_matrix(map_matrix) {}

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

Map::~Map() {}
