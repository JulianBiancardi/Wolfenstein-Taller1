#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_

//#include <LuaBridge.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <list>
#include <float.h>

#include "game/player.h"
#include "../../../common/src/main/config_loader.h"
#include "../../../common/src/main/packets/packet.h"
#include "game/collision_checker.h"


extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


class Bot {
  public:
  Bot(CollisionChecker& checker, Player &player,
      std::unordered_map<int, Player>& players);
  ~Bot();
  void execute();
  void update_player();
  void load_map(int x, int y, int value /*todo change?*/);
  void set_id_at_players(int id);
  void move_actions();
  void kill_actions();
  Player * find_nearest_player();

 private:
  lua_State * state;
  int id_at_players;
  CollisionChecker& checker;
  Player &player;
  std::unordered_map<int, Player>& players;
  std::list<Player *> attacked_players;
  Player * player_goal;
  void lua_checker(int status);
  void lua_push_table_number(const char * key, const auto value);

  };

#endif //WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
