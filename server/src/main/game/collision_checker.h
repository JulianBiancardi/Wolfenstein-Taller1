#ifndef COLLISION_CHECKER_H
#define COLLISION_CHECKER_H

#include "../map.h"
#include "objects/items/item.h"
#include "../../../../common/src/main/object.h"
#include "player.h"

class CollisionChecker {
 private:
  Map& map;
  std::unordered_map<int, Player>& players;
  std::unordered_map<int, Item*>& items;
  std::vector<Object*>& objects;
  Moveable* ignored;
  bool collides_sprites(const Point& where);

 public:
  CollisionChecker(Map& map, std::unordered_map<int, Player>& players,
                   std::unordered_map<int, Item*>& items,
                   std::vector<Object*>& objects);
  ~CollisionChecker() {}

  bool is_free(const Point& where);
  bool can_move(Point& where, Moveable& who);
  Item* grabbed_item(Player& by_whom);
  int get_collides_player_id(Point& where, Player& who);
  bool collides_players(const Point& where);
};

#endif
