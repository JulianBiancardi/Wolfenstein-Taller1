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

  bool Map::collides_object(Point where);
  bool Map::collides_player(Point where, Moveable &for_whom);

 public:
  Map(Matrix<int> &map_matrix);
  ~Map();

  void add_player(Player &player);
  void add_object(Object &object);
  bool is_wall(size_t x, size_t y);
  bool is_free(Point where, Moveable &for_whom);
  int operator()(size_t x, size_t y);
};

#endif
