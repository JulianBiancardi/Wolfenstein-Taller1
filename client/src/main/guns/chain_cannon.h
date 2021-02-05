#ifndef CHAIN_CANNON_H
#define CHAIN_CANNON_H

#include "gun.h"

class ChainCannon : public Gun {
 public:
  ChainCannon();
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<Object*>& objects) override;

 private:
  const static int bullet_required;
  const static int base_precision;
};

#endif
