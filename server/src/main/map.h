#ifndef MAP_H
#define MAP_H

#define WALL 1  // TODO Remove this and ask in Config

#include <functional>
#include <vector>

#include "../../../../common/src/main/utils/matrix.h"
#include "../../../../common/src/main/utils/point.h"
#include "game/moveable.h"
#include "game/player.h"
#include "game/sprites/sprite.h"
#include "game/sprites/items/items.h"
#include "game/sprites/items/medic_kit.h"
#include "game/sprites/items/blood.h"
#include <unordered_map>

class Map {
 private:
  Matrix<int> map_matrix;
  std::unordered_map<int, Items *> items;
  int items_id_count;
  std::vector<Sprite> sprites;

 public:
  Map(Matrix<int> &map_matrix);
  Map(Map &other);
  ~Map();

  // TODO One method for each item
  void add_medic_kit(const Point &where);
  void add_blood(const Point &where);

  std::unordered_map<int, Items *> &get_items();
  std::vector<Sprite> &get_sprites();
  bool is_wall(size_t x, size_t y);
  int operator()(size_t x, size_t y);
};

#endif
