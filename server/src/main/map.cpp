#include "map.h"

#include "../../../common/src/main/ids/gun_ids.h"
#include "game/objects/items/blood.h"
#include "game/objects/items/bullets.h"
#include "game/objects/items/chain_cannon_item.h"
#include "game/objects/items/chest.h"
#include "game/objects/items/cross.h"
#include "game/objects/items/crown.h"
#include "game/objects/items/cup.h"
#include "game/objects/items/food.h"
#include "game/objects/items/key.h"
#include "game/objects/items/machine_gun_item.h"
#include "game/objects/items/medic_kit.h"
#include "game/objects/items/rocket_launcher_item.h"

Map::Map(std::string& map_name)
    : items(), objects(), players(), players_joined(0), BaseMap(map_name) {}

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

//

void Map::add_bullets(const Point& where, int amount) {
  Bullets* new_bullets = new Bullets(where, amount);
  items.insert({new_bullets->get_id(), new_bullets});
}

/*
void Map::add_spawn_point(const Point& spawn_point) {
  spawn_points.push_back(spawn_point);
}

const Point Map::next_spawn_point() {
  return spawn_points.at(players_joined++);
}*/

void Map::add_blood(const Point& where) {
  Blood* new_blood = new Blood(where);
  items.insert({new_blood->get_id(), new_blood});
}

void Map::add_bullets(const Point& where) {
  add_bullets(where, CL::bullets_amount);
}

void Map::add_chain_cannon(const Point& where) {
  ChainCannonItem* new_chain_cannon = new ChainCannonItem(where);
  items.insert({new_chain_cannon->get_id(), new_chain_cannon});
}

void Map::add_chest(const Point& where) {
  Chest* new_chest = new Chest(where);
  items.insert({new_chest->get_id(), new_chest});
}

void Map::add_cross(const Point& where) {
  Cross* new_cross = new Cross(where);
  items.insert({new_cross->get_id(), new_cross});
}

void Map::add_crown(const Point& where) {
  Crown* new_crown = new Crown(where);
  items.insert({new_crown->get_id(), new_crown});
}

void Map::add_cup(const Point& where) {
  Cup* new_cup = new Cup(where);
  items.insert({new_cup->get_id(), new_cup});
}

void Map::add_food(const Point& where) {
  Food* new_food = new Food(where);
  items.insert({new_food->get_id(), new_food});
}

void Map::add_key(const Point& where) {
  Key* new_key = new Key(where);
  items.insert({new_key->get_id(), new_key});
}

void Map::add_machine_gun(const Point& where) {
  MachineGunItem* new_machine_gun = new MachineGunItem(where);
  items.insert({new_machine_gun->get_id(), new_machine_gun});
}

void Map::add_medic_kit(const Point& where) {
  MedicKit* new_medic_kit = new MedicKit(where);
  items.insert({new_medic_kit->get_id(), new_medic_kit});
}

void Map::add_rocket_launcher(const Point& where) {
  RocketLauncherItem* new_rocket_launcher = new RocketLauncherItem(where);
  items.insert({new_rocket_launcher->get_id(), new_rocket_launcher});
}

// Where is dropped was arbitrary chosen
void Map::add_bullets_drop(Player& dead_player) {
  Point where(dead_player.get_position().getX(),
              dead_player.get_position().getY());
  add_bullets(where, CL::bullets_respawn_amount);
}

// Where is dropped was arbitrary chosen
void Map::add_gun_drop(Player& dead_player) {
  if (dead_player.has_droppable_gun()) {
    Point where(dead_player.get_position().getX() +
                    CL::drop_distance_from_dead_player * CL::items_mask_radio,
                dead_player.get_position().getY());
    switch (dead_player.get_active_gun()) {
      case MACHINE_GUN_ID:
        add_machine_gun(where);
        break;
      case CHAIN_CANNON_ID:
        add_chain_cannon(where);
        break;
      case ROCKET_LAUNCHER_ID:
        add_rocket_launcher(where);
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
    add_key(where);
  }
}

// Possible bug: items can spawn inside walls depending on YAML values
void Map::add_drop(Player& dead_player) {
  add_bullets_drop(dead_player);
  add_gun_drop(dead_player);
  add_key_drop(dead_player);
}

Map::~Map() {
  for (auto item : items) delete item.second;
  for (auto object : objects) delete object;
}

void Map::add_spawn_point(double x, double y) {
  spawn_points.emplace_back(x, y);
}
