#include "collision_checker.h"

CollisionChecker::CollisionChecker(Map &map,
                                   const std::vector<std::reference_wrapper
                                                         <Player>> &players,
                                   std::vector<Sprite> &sprites,
                                   const std::vector<Items *> &items)
    : map(map),
      players(players),
      sprites(sprites),
      ignored(nullptr),
      items(items) {}

bool CollisionChecker::collides_players(Point where) {
  for (auto player : players) {
    if (player.get() != *ignored) {
      if (player.get().occupies(where)) return true;
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

bool CollisionChecker::is_free(Point where) {
  if (map.is_wall(where.getX(), where.getY())) return false;

  if (collides_players(where)) return false;

  if (collides_sprites(where)) return false;

  return true;
}

bool CollisionChecker::can_move(Point where, Moveable &who) {
  ignored = &who;

  bool can_move = false;

  Point mask_checking_point = who.collision_mask_bound(where);
  if (is_free(where) && is_free(mask_checking_point))
    can_move = true;

  ignored = nullptr;

  return can_move;
}

Items *CollisionChecker::grabbed_item(Player &by_whom) {
  for (auto &item : items) {
    if (item->occupies(by_whom.get_position())
        && item->can_be_used_by(by_whom)) {
      return item;
    }
  }
  throw -1; // Couldn't find
}