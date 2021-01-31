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
    : items(), objects(), players(), players_joined(0), BaseMap(map_name) {
  MapLoader loader(players, items, objects, spawn_points);
  loader.load_map(map_name);
}

Map::~Map() {
  for (auto item : items) delete item.second;
  for (auto object : objects) delete object;
}

Map::Map(Matrix<int>& map_matrix)
    : items(), objects(), players(), players_joined(0), BaseMap(map_matrix) {}

/*
Map::Map(Map& other)
    : BaseMap(other.map_matrix),
      objects(other.objects),
      spawn_points_occupied(other.spawn_points_occupied),
      spawn_points(other.spawn_points) {
  for (auto elements : other.items) {  // Deep copies every element
    items.insert({elements.first, elements.second->copy()});
  }
}*/

bool Map::add_player(unsigned int player_id) {
  if (players_joined == player_capacity ||
      players.find(player_id) != players.end()) {
    return false;
  }
  // TODO Remove this. Make map have the spawn points
  spawn_points.push_back(Point(1.5, 1.5));

  Point spawn = spawn_points[players_joined];
  Player new_player(spawn, 0);

  players.insert(std::make_pair(player_id, new_player));
  players_joined++;

  return true;
}

Player& Map::get_player(unsigned int player_id) {
  return players.at(player_id);
}

Item& Map::get_item(unsigned int item_id) {
  return (Item&)(*items.at(item_id));
}

Object* Map::get_object(unsigned int object_id) {
  // FIXME
  return objects.at(object_id);
}

void Map::delete_item(unsigned int item_id) {
  delete items.at(item_id);
  items.erase(item_id);
}

const std::unordered_map<unsigned int, Player>& Map::get_players() const {
  return players;
}

const std::unordered_map<unsigned int, Item*>& Map::get_items() const {
  return items;
}

const std::vector<Object*>& Map::get_objects() const { return objects; }

bool Map::has_one_player() const { return players.size() == 1; }

// Where is dropped was arbitrary chosen
void Map::add_bullets_drop(Player& dead_player) {
  Point where(dead_player.get_position().getX(),
              dead_player.get_position().getY());
  Bullets* dropped_bullets = new Bullets(where, CL::bullets_respawn_amount);
  items.insert({dropped_bullets->get_id(), dropped_bullets});
}

// Where is dropped was arbitrary chosen
void Map::add_gun_drop(Player& dead_player) {
  if (dead_player.has_droppable_gun()) {
    Point where(dead_player.get_position().getX() +
                    CL::drop_distance_from_dead_player * CL::items_mask_radio,
                dead_player.get_position().getY());
    switch (dead_player.get_active_gun()) {
      case MACHINE_GUN_ID: {
        MachineGunItem* new_machine_gun = new MachineGunItem(where);
        items.insert({new_machine_gun->get_id(), new_machine_gun});
        break;
      }
      case CHAIN_CANNON_ID: {
        ChainCannonItem* new_chain_cannon = new ChainCannonItem(where);
        items.insert({new_chain_cannon->get_id(), new_chain_cannon});
        break;
      }
      case ROCKET_LAUNCHER_ID: {
        RocketLauncherItem* new_rocket_launcher = new RocketLauncherItem(where);
        items.insert({new_rocket_launcher->get_id(), new_rocket_launcher});
        break;
      }
      default:
        break;
    }
  }
}

// Where is dropped was arbitrary chosen
void Map::add_key_drop(Player& dead_player) {
  if (dead_player.has_keys()) {
    Point where(dead_player.get_position().getX() -
                    CL::drop_distance_from_dead_player * CL::items_mask_radio,
                dead_player.get_position().getY());
    Key* new_key = new Key(where);
    items.insert({new_key->get_id(), new_key});
  }
}

// Possible bug: items can spawn inside walls depending on YAML values
void Map::add_drop(Player& dead_player) {
  add_bullets_drop(dead_player);
  add_gun_drop(dead_player);
  add_key_drop(dead_player);
}

void Map::add_spawn_point(double x, double y) {
  spawn_points.emplace_back(x, y);
}
