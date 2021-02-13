#include "map.h"

#include <yaml-cpp/yaml.h>

#include "../../../common/src/main/ids/gun_ids.h"
#include "game/objects/items/bullets.h"
#include "game/objects/items/chain_cannon_item.h"
#include "game/objects/items/key.h"
#include "game/objects/items/machine_gun_item.h"
#include "game/objects/items/rocket_launcher_item.h"
#include "map_loader.h"

Map::Map(std::string& map_name)
    : items(), objects(), players(), players_joined(0), dogs_joined(0),
    BaseMap(map_name) {
  MapLoader loader(players, items, objects, spawn_points, dogs);
  loader.load_map(map_name);
}

Map::~Map() {
  for (auto item : items) delete item.second;
  for (auto object : objects) delete object.second;
}

Map::Map(Matrix<int>& map_matrix)
    : items(), objects(), players(), players_joined(0), BaseMap(map_matrix) {}

bool Map::add_player(unsigned int player_id) {
  if (players_joined == player_capacity ||
      players.find(player_id) != players.end()) {
    return false;
  }

  Point spawn = spawn_points[players_joined];
  Player new_player(spawn, 0, player_id);

  players.insert(std::make_pair(player_id, new_player));
  players_joined++;

  return true;
}

bool Map::add_bot(unsigned int player_id) {
  if (dogs_joined >= dogs.size() || players.find(player_id) != players.end()) {
    return false;
  }

    Point dog_point = dogs[dogs_joined];
    Player new_player(dog_point, 0, player_id);

    players.insert(std::make_pair(player_id, new_player));
    dogs_joined++;

    return true;
}

Player& Map::get_player(unsigned int player_id) {
  return players.at(player_id);
}

void Map::delete_player(unsigned int player_id) { players.erase(player_id); }

Item& Map::get_item(unsigned int item_id) {
  return (Item&) (*items.at(item_id));
}

Object* Map::get_object(unsigned int object_id) {
  return objects.at(object_id);
}

bool Map::object_exists(unsigned int object_id) {
  return objects.find(object_id) != objects.end();
}

void Map::delete_item(unsigned int item_id) {
  delete items.at(item_id);
  items.erase(item_id);
}

void Map::delete_object(unsigned int object_id) {
  delete objects.at(object_id);
  objects.erase(object_id);
}

const std::unordered_map<unsigned int, Player>& Map::get_players() const {
  return players;
}

const std::unordered_map<unsigned int, Item*>& Map::get_items() const {
  return items;
}

const std::unordered_map<unsigned int, Object*>& Map::get_objects() const {
  return objects;
}

bool Map::has_one_player() const { return players.size() == 1; }

// Where is dropped was arbitrary chosen
void Map::add_bullets_drop(Player& dead_player) {
  Point where(dead_player.get_position().getX(),
              dead_player.get_position().getY());

  auto dropped_bullets = new Bullets(where, CL::bullets_respawn_amount);
  items.insert({dropped_bullets->get_id(), dropped_bullets});
}

// Where is dropped was arbitrary chosen
void Map::add_gun_drop(Player& dead_player) {
  Point where(dead_player.get_position().getX() +
                  CL::drop_distance_from_dead_player * CL::items_mask_radio,
              dead_player.get_position().getY());

  switch (dead_player.get_active_gun()) {
    case MACHINE_GUN_ID: {
      auto new_machine_gun = new MachineGunItem(where);
      items.insert({new_machine_gun->get_id(), new_machine_gun});
      break;
    }
    case CHAIN_CANNON_ID: {
      auto new_chain_cannon = new ChainCannonItem(where);
      items.insert({new_chain_cannon->get_id(), new_chain_cannon});
      break;
    }
    case ROCKET_LAUNCHER_ID: {
      auto new_rocket_launcher = new RocketLauncherItem(where);
      items.insert({new_rocket_launcher->get_id(), new_rocket_launcher});
      break;
    }
    default:break;
  }
}

// Where is dropped was arbitrary chosen
void Map::add_key_drop(Player& dead_player) {
  Point where(dead_player.get_position().getX() -
                  CL::drop_distance_from_dead_player * CL::items_mask_radio,
              dead_player.get_position().getY());

  auto new_key = new Key(where);
  items.insert({new_key->get_id(), new_key});
}

// Possible bug: items can spawn inside walls depending on YAML values
void Map::add_drop(Player& dead_player) {
  add_bullets_drop(dead_player);

  if (dead_player.has_droppable_gun()) {
    add_gun_drop(dead_player);
  }

  if (dead_player.has_keys()) {
    add_key_drop(dead_player);
  }
}

unsigned int Map::add_rocket(const Point& where, double angle) {
  auto new_rocket =
      new Moveable(where, angle, CL::rocket_speed, 0, CL::rocket_radius);
  objects.insert({new_rocket->get_id(), new_rocket});
  return new_rocket->get_id();
}
