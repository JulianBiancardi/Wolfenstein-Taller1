#ifndef KNIFE_H
#define KNIFE_H
#include "gun.h"

class Knife : public Gun {
 public:
  Knife();
  int shoot(Player& player_shooting, int& current_bullets, Map& map) override;

 private:
  const static int range;
  const static int bullet_required = 0;
};

#endif
