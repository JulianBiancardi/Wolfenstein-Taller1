#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "../../../common/src/main/utils/base_map.h"
#include "../../../common/src/main/utils/matrix.h"
#include "../../../common/src/main/utils/ray.h"
#include "object.h"
#include "player.h"

class Map : public BaseMap {
 private:
  // TODO Upon deleting an object, make sure to also remove from this vector
  // with linear search
  std::vector<std::shared_ptr<Object>> objects_and_players;
  std::unordered_map<unsigned int, std::shared_ptr<Object>> objects;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;

 public:
  explicit Map(Matrix<int>& map_matrix);  // TODO Delete eventually
  explicit Map(const std::string& map_name);
  ~Map();

  /* Returns a reference to all of the objects in the map.
   * Deleting objects from the vector might cause problems.
   */
  std::vector<std::shared_ptr<Object>>& get_objects_and_players();

  /* Returns a constant reference to a player given its id. */
  const Player& get_player(unsigned int player_id) const;

  void add_player(unsigned int player_id, const Ray& position);
  void move_player(unsigned int player_id, unsigned char direction);
  void rotate_player(unsigned int player_id, unsigned char direction);
  Hit trigger_gun(unsigned int player_id);
};

#endif
