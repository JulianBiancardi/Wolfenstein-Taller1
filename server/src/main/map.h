#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include <functional>
#include <vector>

#include "../../../../common/src/main/utils/matrix.h"
#include "../../../../common/src/main/utils/point.h"
#include "game/moveable.h"
#include "game/player.h"
#include "game/sprites/sprite.h"

class Map {
 private:
  Matrix<int> map_matrix;

 public:
  Map(Matrix<int> &map_matrix);
  ~Map();

  bool is_wall(size_t x, size_t y);
  int operator()(size_t x, size_t y);
};

#endif
