#include "map.h"

Map::Map(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

void Map::add_player(Player &player) { players.push_back(player); }

void Map::add_object(Object &object) { objects.push_back(object); }

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

bool Map::collides_player(Point where, Moveable &for_whom) {
  for (auto player : players) {
    if (player.get() != for_whom) {
      if (player.get().occupies(where)) return true;
    }
  }

  return false;
}

bool Map::collides_object(Point where) {
  for (auto object : objects) {
    if (object.get().occupies(where)) return true;
  }

  return false;
}

bool Map::is_free(Point where, Moveable &for_whom) {
  if (is_wall(where.getX(), where.getY())) return false;

  if (collides_player(where, for_whom)) return false;

  if (collides_object(where)) return false;

  return true;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}