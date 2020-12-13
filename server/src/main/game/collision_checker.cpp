#include "collision_checker.h"

CollisionChecker::CollisionChecker(Map &map,
                                   std::vector<Player> &players,
                                   std::vector<Sprite> &sprites)
    : map(map), players(players), sprites(sprites) {}

bool CollisionChecker::collides_players(Point where, Moveable &who) {
  for (auto &player : players) {
    if (player != who) {
      if (player.occupies(where)) return true;
    }
  }

  return false;
}

bool CollisionChecker::collides_sprites(Point where) {
  for (auto &sprite : sprites) {
    if (sprite.occupies(where)) return true;
  }

  return false;
}

bool CollisionChecker::can_move(Point where, Moveable &who) {
  if (map.is_wall(where.getX(), where.getY())) return false;

  if (collides_players(where, who)) return false;

  if (collides_sprites(where)) return false;

  return true;
}