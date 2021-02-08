#ifndef COLLISION_CHECKER_H
#define COLLISION_CHECKER_H

#include "../map.h"
#include "objects/items/item.h"
#include "objects/object.h"
#include "player.h"

class CollisionChecker {
 private:
  Map& map;
  const std::unordered_map<unsigned int, Player>& players;
  const std::unordered_map<unsigned int, Item*>& items;
  const std::unordered_map<unsigned int, Object*>& objects;
  Moveable* ignored;
  bool collides_sprites(const Point& where);

 public:
  CollisionChecker(Map& map);
  ~CollisionChecker() {}

  bool is_free(const Point& where);
  bool can_move(Point& where, Moveable& who);
  unsigned int grabbed_item(const Player& by_whom);
  bool collides_players(const Point& where);
  int get_knife_range_collides_player_id(Point& where, Player& who);
};

#endif
