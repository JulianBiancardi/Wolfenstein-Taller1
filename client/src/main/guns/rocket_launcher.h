#ifndef ROCKET_LAUNCHER_H
#define ROCKET_LAUNCHER_H
#include "gun.h"

class RocketLauncher {
 private:
  const static int bullet_required;
  const static int base_precision;

 public:
  RocketLauncher();
  void shoot(Player& player_shooting, int& current_bullets, Map& map);
};

#endif
