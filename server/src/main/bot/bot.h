#ifndef WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
#define WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_

#include <float.h>

#include <cstdio>
#include <iostream>
#include <list>
#include <mutex>
#include <vector>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/data_structures/blocking_queue.h"
#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packing.h"
#include "../../main/managers/match.h"
#include "../game/collisions/collision_checker.h"
#include "../game/objects/player.h"

extern "C" {

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

class Bot {
 public:
  Bot(CollisionChecker& checker, Map& map, unsigned int id_at_players,
      BlockingQueue<Packet>& queue, Match* match);

  ~Bot();
  void execute();
  void update_player();
  void load_map(int x, int y, int value /*todo change?*/);
  void rotate_actions();
  void move_actions();
  void kill_actions();
  void rotate_to_player_goal();
  Player* find_nearest_player();
  bool is_dead();

 private:
  BlockingQueue<Packet>& queue;
  std::mutex mutex;
  lua_State* state;
  int id_at_players;
  CollisionChecker& checker;
  Player* player_goal;
  Map& map;
  Match* match;
  void lua_checker(int status);
  void lua_push_table_number(const char* key, const auto value);
  void send_creation_package();
  void send_movement_package(unsigned char direction);
  void send_rotation_package(unsigned char direction);
  void send_damage_package(unsigned int damage);
  void send_set_gun_package();
};

#endif  // WOLFENSTEIN_TALLER1_SERVER_SRC_MAIN_BOT_H_
