#include "collision_checker.h"

CollisionChecker::CollisionChecker(Map& map,
                                   std::unordered_map<int, Player>& players,
                                   std::unordered_map<int, Item*>& items,
                                   std::vector<Object>& objects)
    : map(map),
      players(players),
      items(items),
      objects(objects),
      ignored(nullptr) {}

bool CollisionChecker::collides_players(Point& where) {
  for (auto& player : players) {
    if (player.second != *ignored) {
      if (player.second.occupies(where)) return true;
    }
  }

  return false;
}

bool CollisionChecker::collides_sprites(Point& where) {
  for (auto& sprite : objects) {
    if (sprite.occupies(where)) return true;
  }

  return false;
}

bool CollisionChecker::is_free(Point& where) {
  if (map.is_wall(where.getX(), where.getY())) return false;

  if (collides_players(where)) return false;

  if (collides_sprites(where)) return false;

  return true;
}

bool CollisionChecker::can_move(Point& where, Moveable& who) {
  ignored = &who;

  bool can_move = false;

  Point mask_checking_point = who.collision_mask_bound(where);
  if (is_free(where) && is_free(mask_checking_point)) can_move = true;

  ignored = nullptr;

  return can_move;
}

Item* CollisionChecker::grabbed_item(Player& by_whom) {
  for (auto& item : items) {
    if (item.second->occupies(by_whom.get_position()) &&
        item.second->can_be_used_by(by_whom)) {
      return item.second;
    }
  }
  throw -1;  // TODO Put some error
}