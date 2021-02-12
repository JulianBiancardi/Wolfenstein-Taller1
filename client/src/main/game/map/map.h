#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../../../../common/src/main/utils/matrix.h"
#include "../../../../common/src/main/utils/ray.h"
#include "../entities/identifiable_object.h"
#include "../entities/object.h"
#include "../entities/player.h"
#include "map_loader.h"

class Map : public BaseMap {
 private:
  // TODO Upon deleting an object, make sure to also remove from this vector
  // with linear search
  std::vector<std::weak_ptr<Object>>
      objects_and_players;  // TODO Cambiar nombre a drawables
  std::vector<std::weak_ptr<IdentifiableObject>> players_shootable;

  std::vector<std::shared_ptr<Object>> ambient_objects;
  std::unordered_map<unsigned int, std::shared_ptr<Object>> objects;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
  MapLoader loader;

 public:
  explicit Map(Matrix<int>& map_matrix);  // TODO Delete eventually
  explicit Map(const std::string& map_name);
  ~Map();

  /* Returns a reference to all of the drawable objects in the map. */
  std::vector<std::weak_ptr<Object>>& get_objects_and_players();

  /* Returns a constant reference to a player given its id. */
  const Player& get_player(unsigned int player_id) const;

  void update();
  void add_item(unsigned int item_id, unsigned char item_type, Point pos);
  void add_player(unsigned int player_id, const Ray& position);
  void move_player(unsigned int player_id, unsigned char direction);
  void rotate_player(unsigned int player_id, unsigned char direction);
  void shoot_player(unsigned int player_id, unsigned char damage);
  void change_gun(unsigned int player_id, unsigned char gun_id);
  void use_bullets(unsigned int player_id, unsigned char gun_id);
  void pick_item(unsigned int player_id, unsigned int item_id);
  Hit trigger_gun(unsigned int player_id);
  void untrigger_gun(unsigned int player_id);

  /* The player sent launches a rocket, new rocket with sent id is created */
  void shoot_rocket(unsigned int player_id, unsigned int rocket_id);

  /* Moves the rocket sent */
  void move_rocket(unsigned int rocket_id);
};

#endif
