#include "map.h"

Map::Map(Matrix<int> &map_matrix) : map_matrix(map_matrix) {}

void Map::add_player(Player &player) {
  players.push_back(player);
}

void Map::add_object(Object &object) {
  objects.push_back(object);
}

bool Map::is_wall(size_t x, size_t y) {
  if (map_matrix(x, y) >= WALL) {
    return true;
  }
  return false;
}

bool Map::is_free(size_t x,
                  size_t y,
                  Moveable &for_whom,
                  double movement_angle) {
  if (for_whom.collides_wall(x, y, movement_angle))
    return false;

  for (auto player : players) {
    if ((for_whom.get_position().getX() != player.get().get_position().getX())
        || (for_whom.get_position().getY()
            != player.get().get_position().getY())) {
      if (for_whom.collides(x, y, player.get()))
        return false;
    }
  }
  for (auto object : objects) {
    if (for_whom.collides(x, y, object.get()))
      return false;
  }
  return true;
}

int Map::operator()(size_t x, size_t y) { return map_matrix(x, y); }

Map::~Map() {}