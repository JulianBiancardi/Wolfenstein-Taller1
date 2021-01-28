#ifndef MAP_H
#define MAP_H

#include <functional>
#include <unordered_map>
#include <vector>

#include "../../../../common/src/main/utils/base_map.h"
#include "../../../../common/src/main/utils/matrix.h"
#include "../../../../common/src/main/utils/point.h"
#include "../../../common/src/main/object.h"
#include "game/moveable.h"
#include "game/objects/items/item.h"
#include "game/player.h"

class Map : public BaseMap {
 private:
  std::unordered_map<unsigned int, Item*> items;
  std::vector<Object*> objects;
  std::unordered_map<unsigned int, Player> players;

  unsigned char players_joined;

  void add_bullets(const Point& where, int amount);
  void add_bullets_drop(Player& dead_player);
  void add_gun_drop(Player& dead_player);
  void add_key_drop(Player& dead_player);

 public:
  Map(std::string& map_name);

  Map(Matrix<int>& map_matrix);
  // Map(Map& other);  // Used for testing, TODO decide where to get the map
  // from

  ~Map();

  /* Creates and adds a player to the map.
   * Returns true on success, false otherwise
   */
  bool add_player(unsigned int player_id);

  /* Returns a reference to a player */
  Player& get_player(unsigned int player_id);

  /* Returns a reference to the players */
  const std::unordered_map<unsigned int, Player>& get_players() const;

  /* Returns a reference to the items */
  const std::unordered_map<unsigned int, Item*>& get_items() const;

  /* Returns a reference to the objects */
  const std::vector<Object*> get_objects() const;

  //
  //
  //

  /*
  void add_spawn_point(const Point& spawn_point);
  const Point next_spawn_point();
  */

  // TODO Use only one method
  void add_blood(const Point& where);
  void add_bullets(const Point& where);
  void add_chain_cannon(const Point& where);
  void add_chest(const Point& where);
  void add_cross(const Point& where);
  void add_crown(const Point& where);
  void add_cup(const Point& where);
  void add_food(const Point& where);
  void add_key(const Point& where);
  void add_machine_gun(const Point& where);
  void add_medic_kit(const Point& where);
  void add_rocket_launcher(const Point& where);

  // The drop added depends on dead_player items
  void add_drop(Player& dead_player);
};

#endif
