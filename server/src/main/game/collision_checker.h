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

  bool collides_objects(const Point& where);

 public:
  explicit CollisionChecker(Map& map);
  ~CollisionChecker() = default;

  /* Returns if the map is free in the given position */
  bool is_free(const Point& where);

  /* Returns if the moveable can move to the given position */
  bool can_move(const Point& where, Moveable& who);

  /* Returns the id of the item grabbed in the player's current position.
   * If there is no item grabbed, it returns 0.
   */
  unsigned int grabbed_item(const Player& by_whom);

  /* Returns a vector with all the players in a distance to where lower than radius. */
  std::vector<unsigned int> get_players_in_radius(const Point& where,
                                                  double radius);

  bool collides_players(const Point& where);

  int get_knife_range_collides_player_id(Point& where, Player& who);
};

#endif
