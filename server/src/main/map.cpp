#include "map.h"
#include "game/objects/items/blood.h"
#include "game/objects/items/bullets.h"
#include "game/objects/items/chain_cannon_item.h"
#include "game/objects/items/food.h"
#include "game/objects/items/key.h"
#include "game/objects/items/machine_gun_item.h"
#include "game/objects/items/medic_kit.h"
#include "game/objects/items/rocket_launcher_item.h"

Map::Map(Matrix<int>& map_matrix)
    : BaseMap(map_matrix), spawn_points_occupied(0) {}

Map::Map(Map& other)
    : BaseMap(other.map_matrix),
      objects(other.objects),
      spawn_points_occupied(other.spawn_points_occupied),
      spawn_points(other.spawn_points) {
  for (auto elements : other.items) {  // Deep copies every element
    items.insert({elements.first, elements.second->copy()});
  }
}

void Map::add_spawn_point(const Point& spawn_point) {
  spawn_points.push_back(spawn_point);
}

const Point Map::next_spawn_point() {
  return spawn_points.at(spawn_points_occupied++);
}

void Map::add_blood(const Point& where) {
  Blood* new_blood = new Blood(where);
  items.insert({new_blood->get_id(), new_blood});
}

void Map::add_bullets(const Point& where) {
  Bullets* new_bullets = new Bullets(where);
  items.insert({new_bullets->get_id(), new_bullets});
}

void Map::add_chain_cannon(const Point& where) {
  ChainCannonItem* new_chain_cannon = new ChainCannonItem(where);
  items.insert({new_chain_cannon->get_id(), new_chain_cannon});
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

std::unordered_map<int, Item*>& Map::get_items() { return items; }

std::vector<Object*>& Map::get_objects() { return objects; }

Map::~Map() {
  for (auto item : items) delete item.second;
  for (auto object : objects) delete object;
}