#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <functional>
#include <unordered_map>
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
  std::unordered_map<unsigned int, Player> players;

 public:
  explicit Map(Matrix<int>& map_matrix);  // TODO Delete eventually
  explicit Map(const std::string& map_name);
  ~Map();

  std::vector<Object*>& get_objects();

  void add_player(Object* player);
  void move_player(unsigned int player_id, unsigned char direction);
  void rotate_player(unsigned int player_id, unsigned char direction);
  // void add_sprite(Sprite &sprite);
};

#endif
