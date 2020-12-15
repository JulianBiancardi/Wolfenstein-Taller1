#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_COLLISION_CHECKER_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_COLLISION_CHECKER_H_

#include "../map.h"
#include "player.h"
#include "sprites/sprite.h"

class CollisionChecker {
 private:
  Map &map;
  std::vector<std::reference_wrapper<Player>> players;
  std::vector<Sprite> &sprites;
  Moveable *ignored;

  bool collides_players(Point where);
  bool collides_sprites(Point where);
  bool is_free(Point where);

 public:
  CollisionChecker(Map &map,
                   const std::vector<std::reference_wrapper<Player>> &players,
                   std::vector<Sprite> &sprites);
  ~CollisionChecker() {}

  bool can_move(Point where, Moveable &who);
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_COLLISION_CHECKER_H_
