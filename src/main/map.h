#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

<<<<<<< HEAD
#include <functional>
#include <vector>

//#include "server/game/moveable.h"
//#include "server/game/player.h"
=======
#include "utils/matrix.h"
#include "server/game/moveable.h"
#include "server/game/player.h"
#include "server/game/objects/object.h"
#include <vector>
#include <functional>
>>>>>>> dd8c3ea79795c2cbdf33b9fdb1a706e90a6220b8

class Map {
 private:
  Matrix<int> map_matrix;
<<<<<<< HEAD
  // std::vector<std::reference_wrapper<Player>> players;
=======
  std::vector <std::reference_wrapper<Player>> players;
  std::vector <std::reference_wrapper<Object>> objects;

  bool Map::collides_object(Point where);
  bool Map::collides_player(Point where, Moveable &for_whom);
>>>>>>> dd8c3ea79795c2cbdf33b9fdb1a706e90a6220b8

 public:
  Map(Matrix<int> &map_matrix);
  ~Map();

<<<<<<< HEAD
  // void add_player(Player &player);
  bool is_wall(size_t x, size_t y);
  // bool is_free(size_t x, size_t y, Moveable &for_whom, double
  // movement_angle);
=======
  void add_player(Player &player);
  void add_object(Object &object);
  bool is_wall(size_t x, size_t y);
  bool is_free(Point where, Moveable &for_whom);
>>>>>>> dd8c3ea79795c2cbdf33b9fdb1a706e90a6220b8
  int operator()(size_t x, size_t y);
};

#endif
