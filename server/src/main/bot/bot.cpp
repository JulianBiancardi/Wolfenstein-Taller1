#include "bot.h"

#define MOVE_EVENT 2
//#define GRAB 3
#define DAMAGE_EVENT 4
#define LUA_PATH "../src/main/bot/script.lua"
#include "../../../../common/src/main/ids/gun_ids.h"

Bot::Bot(CollisionChecker& checker, Map& map, unsigned int id_at_players,
         BlockingQueue<Packet>& queue, Match& match)
    : checker(checker), map(map), id_at_players(id_at_players),
    player_goal(nullptr), queue(queue), match(match) {
  map.get_player(id_at_players).change_gun(KNIFE_ID);  //TODO should not be here.
  send_set_gun_package();
  this->state = luaL_newstate();
  luaL_openlibs(this->state);

  lua_checker(luaL_loadfile(this->state, LUA_PATH));
  lua_checker(lua_pcall(this->state, 0, 0, 0));
  lua_checker(lua_getglobal(this->state, "init"));

  lua_newtable(this->state);

  lua_push_table_number("move", MOVE_EVENT);
  lua_push_table_number("damage", DAMAGE_EVENT);

  lua_pushnumber(this->state, ConfigLoader::player_pace);
  lua_pushnumber(this->state, ConfigLoader::bot_positions_difference_allowed);
  lua_checker(lua_pcall(this->state, 3, 0, 0));
}
void Bot::kill_actions() {
  unsigned int damage_done = lua_tonumber(this->state, -1);
  lua_pop(this->state, 1);
  player_goal->receive_damage(damage_done); //TODO should not be here.
  send_damage_package(damage_done);
}

void Bot::move_actions() {
  float x, y;
  if (lua_istable(this->state, -1)) {
    lua_pushstring(this->state, "x");
    lua_gettable(this->state, -2);
    x = lua_tonumber(this->state, -1);
    lua_pop(this->state, 1);

    lua_pushstring(this->state, "y");
    lua_gettable(this->state, -2);
    y = lua_tonumber(this->state, -1);

    lua_pop(this->state, 1);
  }
  Point new_point(x, y);

  if (player_goal != nullptr &&
      checker.get_knife_range_collides_player_id(
          new_point, map.get_player(id_at_players)) == player_goal->get_id()) {
    if (checker.can_move(new_point, map.get_player(id_at_players))){
      /*TODO should not be here.*/
      map.get_player(id_at_players).set_position(Point(x, y));
      send_rotation_package();
      send_movement_package(map.get_player(id_at_players).
          get_position().movement_direction(new_point));
    }
    lua_checker(lua_getglobal(this->state, "setKilling"));
    lua_checker(lua_pcall(this->state, 0, 0, 0));
  } else if (checker.can_move(new_point, map.get_player(id_at_players))) {
    send_movement_package(map.get_player(id_at_players).
    get_position().movement_direction(new_point));
    map.get_player(id_at_players).set_position(Point(x, y));
  } else {
    lua_checker(lua_getglobal(this->state, "resetMoving"));
    lua_checker(lua_pcall(this->state, 0, 0, 0));
    player_goal = nullptr;
  }
}

Player *Bot::find_nearest_player() {
  int least_distance_player_id;
  float least_distance = FLT_MAX;
  Point least_distance_point(map.get_player(id_at_players).get_position().getX(),
                             map.get_player(id_at_players).get_position().getY());
  for (auto &player : map.get_players()) {
    float dx = std::abs(map.get_player(id_at_players).get_position().getX() -
                        player.second.get_position().getX());
    float dy = std::abs(map.get_player(id_at_players).get_position().getY() -
                        player.second.get_position().getY());
    float distance = 1 * (dx + dy) + (std::sqrt(2) - 2 * 1) * std::min(dx, dy);
    int id_attacked = player.second.get_id();
    bool was_attacked = std::find_if(attacked_players.begin(),
                     attacked_players.end(),
                     [id_attacked](int p_id) {
                       return p_id == id_attacked;
                     }) != attacked_players.end();
    if (was_attacked) continue;
    if ((distance < least_distance) && (distance != 0) && (!player.second.is_dead())) {
      least_distance = distance;
      least_distance_point = player.second.get_position();
      least_distance_player_id = player.second.get_id();
    }
  }
  if (least_distance != FLT_MAX) {
    attacked_players.push_back(least_distance_player_id);
    return &map.get_player(least_distance_player_id);
  } else {
    return 0;
  }
}

void Bot::execute() {
  lua_checker(lua_getglobal(this->state, "decision"));
  lua_checker(lua_pcall(this->state, 0, 1, 0));

  int what_to_do = lua_tonumber(this->state, -1);
  lua_pop(this->state, 1);

  if (what_to_do == 1) {
    player_goal = find_nearest_player();
    if (player_goal == nullptr) {
      lua_checker(lua_getglobal(this->state, "random_movement"));
      lua_checker(lua_pcall(this->state, 0, 2, 0));
    } else {
      lua_checker(lua_getglobal(this->state, "execute"));
      lua_pushnumber(this->state, player_goal->get_position().getX());
      lua_pushnumber(this->state, player_goal->get_position().getY());
      lua_pushnumber(this->state, player_goal->get_id());
      lua_checker(lua_pcall(this->state, 3, 2, 0));
    }
  } else if (what_to_do == 2) {
    lua_checker(lua_getglobal(this->state, "kill"));
    lua_checker(lua_pcall(this->state, 0, 2, 0));
  } else if (what_to_do == 3) {
    lua_checker(lua_getglobal(this->state, "updatePath"));
    lua_pushnumber(this->state, player_goal->get_position().getX());
    lua_pushnumber(this->state, player_goal->get_position().getY());
    lua_pushnumber(this->state, player_goal->get_id());
    lua_checker(lua_pcall(this->state, 3, 2, 0));
  }
  int type = lua_tonumber(this->state, -1);
  lua_pop(this->state, 1);

  switch (type) {
    case MOVE_EVENT:
      move_actions();
      break;
    case DAMAGE_EVENT:
      kill_actions();
      break;
  }
}
void Bot::update_player() {
  lua_checker(lua_getglobal(this->state, "updatePlayer"));
  lua_newtable(this->state);
  lua_push_table_number("posX", map.get_player(id_at_players).get_position().getX());
  lua_push_table_number("posY", map.get_player(id_at_players).get_position().getY());
  lua_push_table_number("walking", 1);
  lua_push_table_number("angle", map.get_player(id_at_players).get_angle());
  lua_newtable(this->state);

  if (player_goal != nullptr) {
    Point own_position = map.get_player(id_at_players).get_position();
    lua_push_table_number("health", player_goal->get_health());
  }
  lua_checker(lua_pcall(this->state, 2, 0, 0));
}

void Bot::load_map(int x, int y, int value) {
  lua_checker(lua_getglobal(this->state, "loadMap"));
  lua_pushnumber(this->state, x);
  lua_pushnumber(this->state, y);
  lua_pushnumber(this->state, value);
  lua_checker(lua_pcall(this->state, 3, 0, 0));
}

Bot::~Bot() {
  if (this->state) lua_close(this->state);
}

void Bot::lua_checker(const int status) {
  if (status > 0)
    std::cout << lua_tostring(this->state, -1) << std::endl;
}

void Bot::lua_push_table_number(const char *key, const auto value) {
  lua_pushstring(this->state, key);
  lua_pushnumber(this->state, value);
  lua_settable(this->state, -3);
}

void Bot::send_movement_package(unsigned char direction) {
  unsigned char data[MOVEMENT_SIZE];
  size_t size = pack(data, "CICC", MOVEMENT, id_at_players,
              (unsigned char)match.get_id(), dire.ction);
  queue.enqueue(Packet(size, data));
}

void Bot::send_rotation_package() {
  double angle = map.get_player(id_at_players).get_position().
      angle_to(player_goal->get_position());
  unsigned char data[ROTATION_SIZE];
  size_t size = pack(data, "CICC", ROTATION, id_at_players,
                     (unsigned char) match.get_id(), angle);
  queue.enqueue(Packet(size, data));
}

void Bot::send_damage_package(unsigned int damage) {
  unsigned char data[SHOT_SIZE];
  size_t size = pack(data, "CICII", SHOT, id_at_players,
                     (unsigned char) match.get_id(), damage,
                     player_goal->get_id());
  queue.enqueue(Packet(size, data));
}

void Bot::send_set_gun_package() {
  unsigned char data[CHANGE_GUN_SIZE];
  size_t size = pack(data, "CICC", CHANGE_GUN, id_at_players,
                     (unsigned char)match.get_id(), KNIFE_ID);
  queue.enqueue(Packet(size, data));
  map.get_player(id_at_players).get_active_gun();

}