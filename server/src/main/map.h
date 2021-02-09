#ifndef MAP_H
#define MAP_H

#include <functional>
#include <unordered_map>
#include <vector>

#include "../../../../common/src/main/utils/base_map.h"
#include "../../../../common/src/main/utils/matrix.h"
#include "../../../../common/src/main/utils/point.h"
#include "game/moveable.h"
#include "game/objects/items/item.h"
#include "game/objects/object.h"
#include "game/player.h"

class Map : public BaseMap {
 private:
  std::unordered_map<unsigned int, Item*> items;
  std::unordered_map<unsigned int, Object*> objects;
  std::unordered_map<unsigned int, Player> players;
  std::vector<Point> spawn_points;

  unsigned char players_joined;

  void add_bullets_drop(Player& dead_player);
  void add_gun_drop(Player& dead_player);
  void add_key_drop(Player& dead_player);

 public:
  explicit Map(std::string& map_name);

  explicit Map(Matrix<int>& map_matrix);

  ~Map();

  /* Creates and adds a player to the map.
   * Returns true on success, false otherwise
   */
  bool add_player(unsigned int player_id);

  /* Returns a reference to a player */
  Player& get_player(unsigned int player_id);

  /* Deletes player */
  void delete_player(unsigned int player_id);

  /* Returns a reference to an item */
  Item& get_item(unsigned int item_id);

  /* Returns a pointer to an object */
  Object* get_object(unsigned int object_id);

  /* Returns if it has the object */
  bool object_exists(unsigned int object_id);

  /* Deletes an item */
  void delete_item(unsigned int item_id);

  /* Deletes an object */
  void delete_object(unsigned int object_id);

  /* Returns a reference to the players */
  const std::unordered_map<unsigned int, Player>& get_players() const;

  /* Returns a reference to the items */
  const std::unordered_map<unsigned int, Item*>& get_items() const;

  /* Returns a reference to the objects */
  const std::unordered_map<unsigned int, Object*>& get_objects() const;

  /* Returns if only has one player or not */
  bool has_one_player() const;

  /* Adds player's death drop */
  void add_drop(Player& dead_player);

  /* Adds a new rocket at the given position */
  unsigned int add_rocket(const Point& where, double angle);
};

#endif
