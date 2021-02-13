#include "collision_checker.h"

CollisionChecker::CollisionChecker(Map& map)
    : map(map),
      players(map.get_players()),
      items(map.get_items()),
      objects(map.get_objects()),
      ignored(nullptr) {}

bool CollisionChecker::collides_players(const Point& where) {
  for (auto& player : players) {
    if (ignored == nullptr || &player.second != ignored) {
      if ((player.second.occupies(where)) && (!player.second.is_dead())) {
        return true;
      }
    }
  }

  return false;
}

bool CollisionChecker::collides_objects(const Point& where) {
  for (auto& object : objects) {
    if (ignored == nullptr || object.second != ignored) {
      if (object.second->occupies(where)) {
        return true;
      }
    }
  }

  return false;
}

bool CollisionChecker::is_free(const Point& where) {
  if (map.is_wall(where.getX(), where.getY())) return false;

  if (collides_players(where)) return false;

  if (collides_objects(where)) return false;

  return true;
}

bool CollisionChecker::can_move(const Point& where, Moveable& who) {
  ignored = &who;

  bool can_move = false;

  Point mask_checking_point = who.collision_mask_bound(where);
  if (is_free(where) && is_free(mask_checking_point)) can_move = true;

  ignored = nullptr;

  return can_move;
}

unsigned int CollisionChecker::grabbed_item(const Player& by_whom) {
  Point position = by_whom.get_position();

  unsigned int item_id = 0;

  for (auto it = items.begin(); it != items.end() && item_id == 0; it++) {
    if (it->second->occupies(position)) {
      item_id = it->second->get_id();
    }
  }

  return item_id;
}

std::vector<unsigned int> CollisionChecker::get_players_in_radius(
    const Point& where, double radius) {
  std::vector<unsigned int> players_in_radio;

  for (const auto& pair : players) {
    const Player& player = pair.second;
    if (player.get_position().distance_from(where) <= radius) {
      players_in_radio.push_back(player.get_id());
    }
  }

  return players_in_radio;
}

int CollisionChecker::get_knife_range_collides_player_id(Point& where,
                                                         Player& who) {
  ignored = &who;
  int id_found = 0;
  for (auto& player : players) {
      if ( (&player.second != ignored)
          && (!player.second.is_dead())
          && (player.second.get_position().distance_from(where) <=
          CL::player_knife_mask_radio))
        id_found = player.second.get_id();
  }
  ignored = nullptr;
  return id_found;
}