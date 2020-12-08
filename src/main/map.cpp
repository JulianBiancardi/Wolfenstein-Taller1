#include "map.h"

Map::Map(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

void Map::add_player(Player &player) { players.push_back(player); }

void Map::add_sprite(Sprite &sprite) { sprites.push_back(sprite); }

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

bool Map::collides_players(Point where, Moveable &for_whom) {
  for (auto player : players) {
    if (player.get() != for_whom) {
      if (player.get().occupies(where)) return true;
    }
  }

  return false;
}

bool Map::collides_sprites(Point where) {
  for (auto sprite : sprites) {
    if (sprite.get().occupies(where)) return true;
  }

  return false;
}

bool Map::is_free(Point where, Moveable &for_whom) {
  if (is_wall(where.getX(), where.getY())) return false;

  if (collides_players(where, for_whom)) return false;

  if (collides_sprites(where)) return false;

  return true;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}