#ifndef MACHINE_GUN_H
#define MACHINE_GUN_H

#include "gun.h"

class MachineGun : public Gun {
 private:
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  MachineGun();
  ~MachineGun();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger() override;
};

#endif
