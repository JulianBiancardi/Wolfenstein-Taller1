#ifndef CHAIN_CANNON_H
#define CHAIN_CANNON_H

#include "gun.h"

class ChainCannon : public Gun {
 private:
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  ChainCannon();
  ~ChainCannon();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger() override;
};

#endif
