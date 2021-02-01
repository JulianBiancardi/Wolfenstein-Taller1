#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <functional>
#include <vector>

#include "../../../common/src/main/object.h"
#include "../../../common/src/main/utils/base_map.h"
#include "../../../common/src/main/utils/matrix.h"

class Map : public BaseMap {
 private:
  // std::vector<std::reference_wrapper<Player>> players;
  // std::vector<std::reference_wrapper<Sprite>> sprites;
  std::vector<Object*> objects;

 public:
  explicit Map(Matrix<int>& map_matrix);
  explicit Map(const std::string& map_name);
  ~Map();

  std::vector<Object*>& get_objects();

  void add_player(Object* player);
  // void add_sprite(Sprite &sprite);
};

#endif
