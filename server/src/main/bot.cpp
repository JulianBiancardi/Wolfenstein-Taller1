#include "bot.h"

#define MOVE 2
//#define GRAB 3
#define DAMAGE 4

#include "../../../common/src/main/ids/gun_ids.h"

Bot::Bot(CollisionChecker &checker, Map &map, int id_at_players)
    : checker(checker), map(map), id_at_players(id_at_players),
    player_goal(nullptr) {
  map.get_player(id_at_players).change_gun(KNIFE_ID);
  map.get_player(id_at_players).get_active_gun();

  this->state = luaL_newstate();
  luaL_openlibs(this->state);

  lua_checker(luaL_loadfile(this->state, "../src/main/script.lua"));
  lua_checker(lua_pcall(this->state, 0, 0, 0));
  lua_checker(lua_getglobal(this->state, "init"));

  lua_newtable(this->state);

  lua_push_table_number("move", MOVE);
  lua_push_table_number("grab", GRAB);
  lua_push_table_number("damage", DAMAGE);

  lua_pushnumber(this->state, ConfigLoader::player_pace);

  lua_pushnumber(this->state, ConfigLoader::bot_positions_difference_allowed);

  lua_checker(lua_pcall(this->state, 3, 0, 0));
}

void Bot::kill_actions() {
   //printf("|KILL ACTIONS|\n");
  int damage_done = lua_tonumber(this->state, -1);
  lua_pop(this->state, 1);
  //printf("DAMAGE DONE: %i", player_goal->get_health());
  player_goal->receive_damage(damage_done);
   //if (player_goal->is_dead())
   //printf("MUERTO %d", player_goal->get_id());
}

void Bot::move_actions() {
  // printf("|MOVE ACTIONS|\n");
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
    if (checker.can_move(new_point, map.get_player(id_at_players)))
      map.get_player(id_at_players).set_position(Point(x, y));
    // Pedirle el punto de su centro al que colisiona.

    // send rotation packet.
    double angle = map.get_player(id_at_players).get_position().
        angle_to(player_goal->get_position());

    lua_checker(lua_getglobal(this->state, "setKilling"));
    lua_checker(lua_pcall(this->state, 0, 0, 0));
  } else if (checker.can_move(new_point, map.get_player(id_at_players))) {
    map.get_player(id_at_players).set_position(Point(x, y));
  } else {
    lua_checker(lua_getglobal(this->state, "resetMoving"));
    lua_checker(lua_pcall(this->state, 0, 0, 0));
    player_goal = nullptr;
  }

   //printf(" Actualizacion:[%f][%f]",x,y);
   //printf("Player:[%f][%f]",map.get_player(id_at_players).get_position().getX()
   // ,map.get_player(id_at_players).get_position().getY());
   //printf("\n");
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

    bool was_attacked =

        std::find_if(attacked_players.begin(), attacked_players.end(),
                     [id_attacked](int p_id) {
                       return p_id == id_attacked;
                     }) != attacked_players.end();

    if (was_attacked) continue;


    if ((distance < least_distance) && (distance != 0) &&
        (!player.second.is_dead())) {
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

   //printf("WHAT TO DO %i", what_to_do);

  if (what_to_do == 1) {
    player_goal = find_nearest_player();
    if (player_goal == nullptr) {
      lua_checker(lua_getglobal(this->state, "random_movement"));
      lua_checker(lua_pcall(this->state, 0, 2, 0));
    } else {
      // printf("FUERON PLAYER GOAL: %i", player_goal->get_id());

      lua_checker(lua_getglobal(this->state, "execute"));

      lua_pushnumber(this->state, player_goal->get_position().getX());
      lua_pushnumber(this->state, player_goal->get_position().getY());
      lua_pushnumber(this->state, player_goal->get_id());
      lua_checker(lua_pcall(this->state, 3, 2, 0));
    }
  } else if (what_to_do == 2) {
    // kill
    lua_checker(lua_getglobal(this->state, "kill"));
    lua_checker(lua_pcall(this->state, 0, 2, 0));
  } else if (what_to_do == 3) {
    lua_checker(lua_getglobal(this->state, "updatePath"));
    lua_pushnumber(this->state, player_goal->get_position().getX());
    lua_pushnumber(this->state, player_goal->get_position().getY());
    lua_pushnumber(this->state, player_goal->get_id());
    //printf(".%d.", player_goal->get_id());
    lua_checker(lua_pcall(this->state, 3, 2, 0));
  }

  int type = lua_tonumber(this->state, -1);
  lua_pop(this->state, 1);
  switch (type) {
    case MOVE:
      move_actions();
      break;
      // case GRAB:
      // break;
    case DAMAGE:
      kill_actions();
      break;
    default:
      break;
  }

  // todo server event
  //  auto event = ServerCommand::create(key, action);
  //  if (event)
  //  queue.push(std::move(event));
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

void Bot::load_map(int x, int y, int value /*todo change*/) {
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
  if (status > 0) std::cout << lua_tostring(this->state, -1) << std::endl;
}

void Bot::lua_push_table_number(const char *key, const auto value) {
  lua_pushstring(this->state, key);
  lua_pushnumber(this->state, value);
  lua_settable(this->state, -3);
}