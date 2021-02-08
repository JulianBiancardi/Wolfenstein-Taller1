#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>

#include "../../../common/src/main/utils/base_map.h"
#include "../../../common/src/main/utils/point.h"
#include "../../../common/src/main/utils/ray.h"
#include "guns/gun.h"
#include "guns/hit.h"

class Gun;

class Player : public Object {
 private:
  double pace;
  int health;
  int bullets;
  std::unordered_map<int, Gun*> guns_bag;
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

  //
  void add_gun(int gun_num, Gun* gun);
  void set_gun(int gun_num);
  int get_health();
  void set_health(int health);
  bool has_bullets(int bullets);
  void decrease_bullets(int amount);

  Hit shoot(BaseMap& map, const std::vector<Object*>& map_objects);
};

#endif
