#include "collision_checker.h"

CollisionChecker::CollisionChecker(Map& map)
    : map(map),
      players(map.get_players()),
      items(map.get_items()),
      objects(map.get_objects()),
      ignored(nullptr) {}

bool CollisionChecker::collides_players(const Point& where) {
  for (auto& player : players) {
    if (ignored == nullptr || player.second != *ignored) {
      if ((player.second.occupies(where)) && (!player.second.is_dead())) {
        return true;
      }
    }
  }

  return false;
}

bool CollisionChecker::collides_sprites(const Point& where) {
  for (auto& object : objects) {
    if (object->occupies(where)) return true;
  }

  return false;
}

bool CollisionChecker::is_free(const Point& where) {
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
  Point player_position(by_whom.get_position());
  for (auto& item : items) {
    if (item.second->occupies(player_position) &&
        item.second->can_be_used_by(by_whom)) {
      return item.second;
    }
  }
  throw -1;  // TODO Put some error
}
//

int CollisionChecker::get_collides_player_id(Point& where, Player& who) {
  ignored = &who;
  Point mask_checking_point = who.collision_mask_bound(where);
  int id_found = 0;
  for (auto& player : players) {
    if (player.second != *ignored) {
      if ((player.second.occupies(mask_checking_point)) &&
          (!player.second.is_dead())) {
        id_found = player.second.get_id();
      }
    }
  }
  ignored = nullptr;
  return id_found;
}
