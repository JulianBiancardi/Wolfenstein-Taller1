#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <functional>
#include <vector>

#include "../../../common/src/main/object.h"
#include "../../../common/src/main/utils/base_map.h"
#include "../../../common/src/main/utils/matrix.h"
#include "player.h"

class Map : public BaseMap {
 private:
  // std::vector<std::reference_wrapper<Player>> players;
  // std::vector<std::reference_wrapper<Sprite>> sprites;
  std::vector<Object*> objects;

 public:
  Map(Matrix<int>& map_matrix);
  ~Map();

  std::vector<Object*>& get_objects();

  void add_player(Player* player);
  // void add_sprite(Sprite &sprite);
};

#endif
