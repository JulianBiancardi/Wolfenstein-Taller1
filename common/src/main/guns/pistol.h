#ifndef WOLFENSTEIN_TALLER1_PISTOL_H
#define WOLFENSTEIN_TALLER1_PISTOL_H

#include "../player.h"
#include "gun.h"
#include "spray.h"

class Pistol : public Gun {
 private:
  /*int bullet_required;
  int base_precision;*/
  Spray spray;

 public:
  Pistol();
  ~Pistol();

  int shoot(Player& player_shooting, int& current_bullets, Map& map) override;
};

#endif  // WOLFENSTEIN_TALLER1_GUN_H
