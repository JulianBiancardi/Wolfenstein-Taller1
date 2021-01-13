#ifndef BASE_MAP_H
#define BASE_MAP_H

#include "matrix.h"
//#include <iostream>

class BaseMap {
 protected:
  Matrix<int> map_matrix;

 public:
  BaseMap(Matrix<int>& map_matrix);
  ~BaseMap();

  bool is_wall(size_t x, size_t y);
  int operator()(size_t x, size_t y);
};

#endif