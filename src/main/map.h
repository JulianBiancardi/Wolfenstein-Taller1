#ifndef MAP_H
#define MAP_H

#include "utils/matrix.h"

class Map {
 private:
  Matrix<int> map_matrix;

 public:
  Map(Matrix<int>& map_matrix);

  // TODO Make move constructor

  bool is_wall(size_t x, size_t y);
  int operator()(size_t x, size_t y);
  ~Map();
};

#endif
