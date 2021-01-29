#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_

//#include <LuaBridge.h>
#include <float.h>

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

#include "../../../common/src/main/config_loader.h"
#include "../../../common/src/main/packets/packet.h"
#include "game/collision_checker.h"
#include "game/player.h"

extern "C" {
/*
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>*/

#include "lua5.1/lauxlib.h"
#include "lua5.1/lua.h"
#include "lua5.1/lualib.h"
}

class Bot {
 public:
  Bot(CollisionChecker& checker, Player& player,
      std::unordered_map<int, Player>& players);
  ~Bot();
  void execute();
  void update_player();
  void load_map(int x, int y, int value /*todo change?*/);
  void set_id_at_players(int id);
  void move_actions();
  void kill_actions();
  void rotate_to_player_goal();
  Player* find_nearest_player();

 private:
  lua_State* state;
  int id_at_players;
  CollisionChecker& checker;
  Player& player;
  std::unordered_map<int, Player>& players;
  std::list<Player*> attacked_players;
  Player* player_goal;
  void lua_checker(int status);
  void lua_push_table_number(const char* key, const auto value);
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
