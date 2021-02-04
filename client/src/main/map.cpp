#include "map.h"

Map::Map(Matrix<int>& map_matrix) : BaseMap(map_matrix) {}

Map::Map(const std::string& map_name) : BaseMap(map_name) {}

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

void Map::move_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id).move(direction);
}

void Map::rotate_player(unsigned int player_id, unsigned char direction) {
  players.at(player_id).rotate(direction);
}
