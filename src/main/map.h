#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include "utils/matrix.h"
#include "server/game/moveable.h"
#include "server/game/player.h"
#include "server/game/objects/object.h"
#include <vector>
#include <functional>

class Map {
 private:
  Matrix<int> map_matrix;
  std::vector <std::reference_wrapper<Player>> players;
  std::vector <std::reference_wrapper<Object>> objects;

 public:
  Map(Matrix<int> &map_matrix);
  void add_player(Player &player);
  void add_object(Object &object);
  bool is_wall(size_t x, size_t y);
  bool is_free(size_t x, size_t y, Moveable &for_whom, double movement_angle);
  int operator()(size_t x, size_t y);
  ~Map();
};

#endif
