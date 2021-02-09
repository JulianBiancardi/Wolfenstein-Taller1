#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <unordered_map>

#include "../../../common/src/main/utils/base_map.h"
#include "../../../common/src/main/utils/point.h"
#include "../../../common/src/main/utils/ray.h"
#include "guns/gun.h"
#include "guns/hit.h"
#include "object.h"

class Gun;

class Player : public Object {
 private:
  int health;
  int bullets;
  int score;
  int keys;
  std::unordered_map<int, std::shared_ptr<Gun>> guns_bag;
  int active_gun;

  // TODO Make copyable since it is stored in STD Containers
 public:
  Player(Ray position, unsigned int player_id);

  Player(const Player& other) = delete;
  Player& operator=(const Player&) = delete;

  Player(Player&& other) = delete;
  Player& operator=(Player&& other) = delete;

  ~Player();

  void move(unsigned char direction);
  void rotate(unsigned char direction);

  /* Receives a gun id and adds it to the guns bag. */
  void add_gun(unsigned int gun_id);

  /* Receives an item ids and adds it to the player. */
  void add_item(unsigned int item_id);

  /* Sets the gun of the player, changing its res_id */
  void set_gun(int gun_num);

  /* Gets the active gun of the player. */
  int get_gun() const;

  /* Returns the health of the player. */
  int get_health() const;
  /* Sets the player health to the given amount. */
  void set_health(int health);

  // TODO Remove this. It isn't used anywhere other than tests.
  bool has_bullets(int bullets);

  /* Returns the amount of bullets owned by the player. */
  int get_bullets() const;

  /* Decreases the amount of bullets owned by the player. */
  void decrease_bullets(unsigned char gun_id);

  /* Grabs an item. */
  void grab_item(Object& item);

  /* Pulls the trigger of the player's gun.
   * Returns a Hit object containing the data of the shot attempt.
   */
  Hit trigger_gun(BaseMap& map,
                  const std::vector<std::shared_ptr<Object>>& map_objects);

  /* Unpulls the trigger of the player's gun. */
  void untrigger_gun();
};

#endif
