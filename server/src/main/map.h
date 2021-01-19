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
#include "../../../common/src/main/object.h"
#include "game/player.h"

class Map : public BaseMap {
 private:
  std::unordered_map<int, Item*> items;
  std::vector<Object*> objects;
  // Used for spawning logic:
  int spawn_points_occupied;
  std::vector<Point> spawn_points;

  void add_bullets(const Point& where, int amount);
  void add_bullets_drop(Player& dead_player);
  void add_gun_drop(Player& dead_player);
  void add_key_drop(Player& dead_player);

 public:
  Map(Matrix<int>& map_matrix);
  Map(Map& other); // Used for testing, TODO decide where to get the map from
  ~Map();

  void add_spawn_point(const Point& spawn_point);
  const Point next_spawn_point();

  // TODO One method for each item
  void add_blood(const Point& where);
  void add_bullets(const Point& where);
  void add_chain_cannon(const Point& where);
  void add_food(const Point& where);
  void add_key(const Point& where);
  void add_machine_gun(const Point& where);
  void add_medic_kit(const Point& where);
  void add_rocket_launcher(const Point& where);

  // The drop added depends on dead_player items
  void add_drop(Player& dead_player);

  std::unordered_map<int, Item*>& get_items();
  std::vector<Object*>& get_objects();
};

#endif
