#ifndef MAP_H
#define MAP_H

#include "utils/matrix.h"
#define WALL 1  // TODO Remove this and ask in Config

#include <functional>
#include <vector>

//#include "server/game/moveable.h"
//#include "server/game/player.h"

class Map {
 private:
  Matrix<int> map_matrix;
  // std::vector<std::reference_wrapper<Player>> players;

 public:
  Map(Matrix<int> &map_matrix);
  ~Map();

  // void add_player(Player &player);
  bool is_wall(size_t x, size_t y);
  // bool is_free(size_t x, size_t y, Moveable &for_whom, double
  // movement_angle);
  int operator()(size_t x, size_t y);
};

#endif
