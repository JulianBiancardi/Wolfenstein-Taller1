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
#include "../entities/items/item.h"
#include "../entities/object.h"
#include "../entities/player.h"
#include "../entities/rocket.h"
#include "map_loader.h"

class Map : public BaseMap {
 private:
  std::vector<std::weak_ptr<Object>> drawables;
  std::vector<std::weak_ptr<IdentifiableObject>> players_shootable;
  // TODO this could be maybe reduced by means of

  // shared_ptrs are used since they must also be kept in drawables
  std::vector<std::shared_ptr<Object>> ambient_objects;
  std::unordered_map<unsigned int, std::shared_ptr<Rocket>> rockets;
  std::unordered_map<unsigned int, std::shared_ptr<Item>> items;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
  MapLoader loader;

 public:
  explicit Map(Matrix<int>& map_matrix);  // TODO Delete eventually
  explicit Map(const std::string& map_name);
  ~Map();

  /* Returns a reference to all of the drawable objects in the map. */
  std::vector<std::weak_ptr<Object>>& get_drawables();

  /* Returns a constant reference to a player given its id. */
  const Player& get_player(unsigned int player_id) const;

  void update();
  void add_item(unsigned int item_id, const Ray& position,
                unsigned char item_type);
  void add_player(unsigned int player_id, const Ray& position);
  void move_player(unsigned int player_id, unsigned char direction);
  void rotate_player(unsigned int player_id, unsigned char direction);
  void shoot_player(unsigned int player_id, unsigned char damage,
                    unsigned int damager_id);
  void change_gun(unsigned int player_id, unsigned char gun_id);
  void use_bullets(unsigned int player_id, unsigned char gun_id);
  int pick_item(unsigned int player_id, unsigned int item_id);
  Hit update_gun(unsigned int player_id, bool trigger);

  /* The player sent launches a rocket, new rocket with sent id is created */
  void shoot_rocket(unsigned int player_id, unsigned int rocket_id);

  /* Moves the rocket sent */
  void move_rocket(unsigned int rocket_id);

  /* Returns the rocket's owner id */
  unsigned int get_rocket_owner_id(unsigned int rocket_id);
};

#endif
