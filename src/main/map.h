#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include "utils/matrix.h"

class Map {
 private:
  Matrix<int> map_matrix;

 public:
  Map(Matrix<int>& map_matrix);
  bool is_wall(size_t x, size_t y);
  int operator()(size_t x, size_t y);
  ~Map();
};

#endif
