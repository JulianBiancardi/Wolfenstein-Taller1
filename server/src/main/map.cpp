#include "map.h"
#include "game/objects/items/blood.h"
#include "game/objects/items/medic_kit.h"
#include "game/objects/items/bullets.h"

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

void Map::add_medic_kit(const Point& where) {
  MedicKit* new_medic_kit = new MedicKit(where);
  items.insert({new_medic_kit->get_id(), new_medic_kit});
}

void Map::add_blood(const Point& where) {
  Blood* new_blood = new Blood(where);
  items.insert({new_blood->get_id(), new_blood});
}

void Map::add_bullets(const Point& where) {
  Bullets* new_bullets = new Bullets(where);
  items.insert({new_bullets->get_id(), new_bullets});
}

std::unordered_map<int, Item*>& Map::get_items() { return items; }

std::vector<Object*>& Map::get_objects() { return objects; }

Map::~Map() {
  for (auto item : items) delete item.second;
  for (auto object : objects) delete object;
}