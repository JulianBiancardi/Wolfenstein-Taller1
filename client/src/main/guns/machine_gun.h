#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H

//#include "../player.h"
#include "gun.h"

class MachineGun : public Gun {
 public:
  MachineGun();
  Hit shoot(Object& player, int& current_bullets, Map& map) override;

 private:
  const static int bullet_required;
  const static int base_precision;
};

#endif
