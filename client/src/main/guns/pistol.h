#ifndef PISTOL_H
#define PISTOL_H

#include "../player.h"
#include "gun.h"
#include "hit.h"
#include "spray.h"

class Pistol : public Gun {
 private:
  Spray spray;

  double linear_func(double x);
  double slope;
  double intercept;

 public:
  Pistol();
  ~Pistol();

  Hit shoot(Player& player_shooting, int& current_bullets, Map& map) override;
};

#endif
