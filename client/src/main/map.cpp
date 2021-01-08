#include "map.h"

Map::Map(Matrix<int>& map_matrix) : BaseMap(map_matrix) {}

// void Map::add_player(Player &player) { players.push_back(player); }

// void Map::add_sprite(Sprite &sprite) { sprites.push_back(sprite); }

Map::~Map() {}

std::vector<Object>& Map::get_objects() { return objects; }