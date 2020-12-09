#include "map.h"

Map::Map(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

// void Map::add_player(Player &player) { players.push_back(player); }

// void Map::add_sprite(Sprite &sprite) { sprites.push_back(sprite); }

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}