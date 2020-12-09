#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include <functional>
#include <vector>

#include "../../../common/src/main/utils/matrix.h"
#include "../../../server/src/main/game/player.h"
#include "../../../server/src/main/game/sprites/sprite.h"

class Map {
 private:
  Matrix<int> map_matrix;
  std::vector<std::reference_wrapper<Player>> players;
  std::vector<std::reference_wrapper<Sprite>> sprites;

  bool collides_sprites(Point where);
  bool collides_players(Point where, Moveable &for_whom);

 public:
  Map(Matrix<int> &map_matrix);
  ~Map();

  void add_player(Player &player);
  void add_sprite(Sprite &sprite);
  bool is_wall(size_t x, size_t y);
  bool is_free(Point where, Moveable &for_whom);
  int operator()(size_t x, size_t y);
};

#endif
