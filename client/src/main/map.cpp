#include "map.h"

Map::Map(Matrix<int>& map_matrix) : BaseMap(map_matrix) {}

void Map::add_player(Object* player) {
  // players.push_back(player);
  // objects.push_back(player);
  objects.push_back((Object*)player);
}

// void Map::add_sprite(Sprite &sprite) { sprites.push_back(sprite); }

Map::~Map() {
  // for (auto object : objects) delete object;
}

std::vector<Object*>& Map::get_objects() { return objects; }
