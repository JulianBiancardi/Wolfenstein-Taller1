#ifndef WOLFENSTEIN_TALLER1_PISTOL_H
#define WOLFENSTEIN_TALLER1_PISTOL_H

#include <random>

#include "../player.h"
#include "gun.h"

class Pistol : public Gun {
 private:
  /*int bullet_required;
  int base_precision;*/

  std::default_random_engine generator;
  std::normal_distribution<double> bloom;

 public:
  Pistol();
  ~Pistol();

  int shoot(Player& player_shooting, int& current_bullets, Map& map) override;
};

#endif  // WOLFENSTEIN_TALLER1_GUN_H
