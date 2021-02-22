#include "map.h"

#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../common/src/main/ids/map_ids.h"
#include "map_loader.h"

Map::Map(Matrix<int>& map_matrix)
    : BaseMap(map_matrix),
      drawables(),
      ambient_objects(),
      items(),
      players(),
      loader(drawables, players_shootable, ambient_objects, items, players,
             rockets) {}

Map::Map(const std::string& map_name)
    : BaseMap(map_name),
      drawables(),
      ambient_objects(),
      items(),
      players(),
      loader(drawables, players_shootable, ambient_objects, items, players,
             rockets) {
  loader.load_map(map_name);
}

Map::~Map() {}

void Map::update() {
  std::unordered_map<unsigned int, std::shared_ptr<Player>>::iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    iter->second->update();
  }
}

void Map::add_item(unsigned char item_type, const Ray& position) {
  loader.add_item(position, item_type);
}

void Map::add_player(unsigned int player_id, const Ray& position) {
  loader.add_player(position, player_id);
}

std::vector<std::weak_ptr<Object>>& Map::get_drawables() { return drawables; }

const Player& Map::get_player(unsigned int player_id) const {
  return *(players.at(player_id));
}

std::vector<std::shared_ptr<Player>> Map::get_players() const {
  std::vector<std::shared_ptr<Player>> players_vector;

  for (const auto& player : players) {
    players_vector.push_back(player.second);
  }

  return players_vector;
}

void Map::move_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->move(direction);
}

void Map::rotate_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id)->rotate(direction);
}

void Map::shoot_player(unsigned int player_id, unsigned char damage,
                       unsigned int damager_id) {
  auto player = players.at(player_id);
  auto damager = players.at(damager_id);

  player->decrease_health(damage);

  if (player->is_dead()) {
    damager->add_kill();
    add_drop(player_id);
    if (player->has_lives_left()) {
      player->respawn();
    } else {
      player->respawn_as_ghost();
    }
  }
}

void Map::change_gun(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->set_gun(gun_id);
}

void Map::use_bullets(unsigned int player_id, unsigned char gun_id) {
  players.at(player_id)->decrease_bullets(gun_id);
}

int Map::pick_item(unsigned int player_id, unsigned int item_id) {
  Player& player = *(players.at(player_id));
  std::shared_ptr<Item> item = items.at(item_id);
  int res_id = item->get_res_id();
  item->use_on(player);
  items.erase(item_id);
  return res_id;
}

Hit Map::update_gun(unsigned int player_id, bool trigger) {
  auto player = players.at(player_id);

  if (player->is_dead()) {
    return std::move(Hit(0, 0, 0, false));
  }

  return std::move(player->update_gun(*this, trigger, players_shootable));
}

void Map::shoot_rocket(unsigned int player_id) {
  use_bullets(player_id, ROCKET_LAUNCHER_ID);
  auto player = players.at(player_id);

  const Point& player_position = player->get_position();
  double angle = player->get_angle();

  double front_x = player_position.getX() + cos(angle) * CL::player_mask_radio;
  double front_y = player_position.getY() - sin(angle) * CL::player_mask_radio;

  Ray spawn_point(front_x, front_y, angle);

  loader.add_rocket(spawn_point, player_id);
}

void Map::move_rocket(unsigned int rocket_id) { rockets.at(rocket_id)->move(); }

unsigned int Map::get_rocket_owner_id(unsigned int rocket_id) {
  return rockets.at(rocket_id)->get_owner_id();
}

void Map::explode_rocket(unsigned int rocket_id) {
  // Show animation here
  rockets.erase(rocket_id);
}

void Map::add_bullets_drop(std::shared_ptr<Player>& dead_player) {
  Ray where(dead_player->get_position().getX(),
            dead_player->get_position().getY(), 0);

  add_item(BULLETS, where);
}

void Map::add_gun_drop(std::shared_ptr<Player>& dead_player) {
  Ray where(dead_player->get_position().getX() +
                CL::drop_distance_from_dead_player * CL::items_mask_radio,
            dead_player->get_position().getY(), 0);

  switch (dead_player->get_gun()) {
    case MACHINE_GUN_ID:
      add_item(MACHINE_GUN, where);
      break;
    case CHAIN_CANNON_ID:
      add_item(CHAIN_CANNON, where);
      break;
    case ROCKET_LAUNCHER_ID:
      add_item(ROCKET_LAUNCHER, where);
      break;
    default:
      break;
  }
}

void Map::add_key_drop(std::shared_ptr<Player>& dead_player) {
  Ray where(dead_player->get_position().getX() -
                CL::drop_distance_from_dead_player * CL::items_mask_radio,
            dead_player->get_position().getY(), 0);

  add_item(KEY, where);
}

void Map::add_drop(unsigned int player_id) {
  auto dead_player = players.at(player_id);
  add_bullets_drop(dead_player);

  if (dead_player->has_droppable_gun()) {
    add_gun_drop(dead_player);
  }

  if (dead_player->has_keys()) {
    add_key_drop(dead_player);
  }
}
