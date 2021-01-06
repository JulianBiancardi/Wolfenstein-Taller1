#include "map.h"

Map::Map(Matrix<int>& map_matrix) : map_matrix(map_matrix), items_id_count(1) {}

// TODO Why is this necessary? The map exists in 1 place and shouldn't be moved,
// I think. -Santi
Map::Map(Map& other)
    : map_matrix(other.map_matrix),
      items_id_count(other.items_id_count),
      objects(other.objects) {
  for (auto elements : other.items) {  // Deep copies every element
    items.insert({elements.first, elements.second->copy()});
  }
}

void Map::add_medic_kit(const Point& where) {
  items.insert({items_id_count, new MedicKit(where, items_id_count)});
  items_id_count++;
}

void Map::add_blood(const Point& where) {
  items.insert({items_id_count, new Blood(where, items_id_count)});
  items_id_count++;
}

std::unordered_map<int, Item*>& Map::get_items() { return items; }

bool Map::is_wall(size_t x, size_t y) { return map_matrix(x, y) >= WALL; }

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

std::vector<Object>& Map::get_objects() { return objects; }

Map::~Map() {
  for (auto item : items) delete item.second;
}