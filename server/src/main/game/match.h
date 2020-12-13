#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_

#include "../map.h"
#include "player.h"
#include "sprites/sprite.h"
#include "collision_checker.h"

class Match {
 private:
  Map &map;
  std::vector<Player> players;
  std::vector<Sprite> sprites;

 public:
  void start();
};

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_GAME_MATCH_H_
