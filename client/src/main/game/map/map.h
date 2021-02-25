#ifndef CLIENT_MAP_H
#define CLIENT_MAP_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../../../../../common/src/main/utils/base_map.h"
#include "../../../../../common/src/main/utils/matrix.h"
#include "../../../../../common/src/main/utils/ray.h"
#include "../entities/doors/base_door.h"
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

  // shared_ptrs are used since they must also be kept in drawables
  std::vector<std::shared_ptr<Object>> ambient_objects;
  std::unordered_map<unsigned int, std::shared_ptr<Rocket>> rockets;
  std::unordered_map<unsigned int, std::shared_ptr<Item>> items;
  std::unordered_map<unsigned int, std::shared_ptr<Player>> players;
  std::unordered_map<std::pair<unsigned int, unsigned int>,
                     std::unique_ptr<BaseDoor>, PairHasher>
      doors;
  MapLoader loader;

  void add_bullets_drop(std::shared_ptr<Player>& dead_player);
  void add_gun_drop(std::shared_ptr<Player>& dead_player);
  void add_key_drop(std::shared_ptr<Player>& dead_player);

 public:
  explicit Map(Matrix<int>& map_matrix);  // TODO Delete eventually
  explicit Map(const std::string& map_name);
  ~Map();

  /* Returns a reference to all of the drawable objects in the map. */
  std::vector<std::weak_ptr<Object>>& get_drawables();

  /* Returns a constant reference to a player given its id. */
  const Player& get_player(unsigned int player_id) const;

  /* Returns a constant reference to a door given its cell. */
  const std::unique_ptr<BaseDoor>& get_door(
      const std::pair<unsigned int, unsigned int>& cell);

  /* Returns true if there is a door in the cell, false otherwise. */
  bool is_door(const std::pair<unsigned int, unsigned int>& cell) const;
  /* Returns players as vector. */
  std::vector<std::shared_ptr<Player>> get_players() const;

  void update();
  void add_item(unsigned char item_type, const Ray& position);
  void add_player(unsigned int player_id, const Ray& position);
  void move_player(unsigned int player_id, unsigned char direction);
  void rotate_player(unsigned int player_id, unsigned char direction);
  void shoot_player(unsigned int player_id, unsigned char damage,
                    unsigned int damager_id);
  void change_gun(unsigned int player_id, unsigned char gun_id);
  void use_bullets(unsigned int player_id, unsigned char gun_id);
  void use_key(unsigned int player_id);
  int pick_item(unsigned int player_id, unsigned int item_id);
  Hit update_gun(unsigned int player_id, bool trigger);

  const std::unique_ptr<BaseDoor>& get_door(
      const std::pair<unsigned int, unsigned int>& cell) const;

  /* The player sent launches a rocket, new rocket is created */
  void shoot_rocket(unsigned int player_id);

  /* Moves the rocket sent */
  void move_rocket(unsigned int rocket_id);

  /* Returns the rocket's owner id */
  unsigned int get_rocket_owner_id(unsigned int rocket_id);

  /* Explodes the rocket */
  void explode_rocket(unsigned int rocket_id);

  /* Adds player's death drop */
  void add_drop(unsigned int player_id);

  /* Player saves its previous gun */
  void make_player_remember_gun(unsigned int player_id);
};

#endif
