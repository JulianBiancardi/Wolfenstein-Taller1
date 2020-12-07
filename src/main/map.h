#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include "matrix.h"
#include "server/game/moveable.h"

class Map {
 private:
  Matrix<int> map_matrix;

 public:
  Map(Matrix<int> &map_matrix);
  bool is_wall(size_t x, size_t y);
  bool is_free(size_t x, size_t y, Moveable &for_whom, double movement_angle);
  int operator()(size_t x, size_t y);
  ~Map();
};

#endif
