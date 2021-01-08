#ifndef WOLFENSTEIN_TALLER1_PISTOL_H
#define WOLFENSTEIN_TALLER1_PISTOL_H

#include "../player.h"
#include "gun.h"

class Pistol : public Gun {
 public:
  Pistol();
  int shoot(Player& player_shooting, int& current_bullets, Map& map) override;

 private:
  /*static*/ int bullet_required;
  /*static*/ int base_precision;
};

#endif  // WOLFENSTEIN_TALLER1_GUN_H
