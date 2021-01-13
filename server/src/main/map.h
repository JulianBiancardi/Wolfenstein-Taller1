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
  std::unordered_map<int, Item*> items;
  int items_id_count;
  std::vector<Object*> objects;

 public:
  Map(Matrix<int>& map_matrix);
  Map(Map& other); // Used for testing, TODO decide where to get the map from
  ~Map();

  // TODO One method for each item
  void add_medic_kit(const Point& where);
  void add_blood(const Point& where);
  void add_bullets(const Point& where);

  std::unordered_map<int, Item*>& get_items();
  std::vector<Object*>& get_objects();
};

#endif
