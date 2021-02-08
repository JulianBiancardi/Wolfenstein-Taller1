#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H

#include "gun.h"

class MachineGun : public Gun {
 public:
  MachineGun();
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<Object*>& objects) override;

 private:
  const static int bullet_required;
  const static int base_precision;
};

#endif
