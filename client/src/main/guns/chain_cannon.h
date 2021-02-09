#ifndef CHAIN_CANNON_H
#define CHAIN_CANNON_H

#include <SDL2/SDL.h>

#include "gun.h"
#include "hit.h"
#include "spray.h"

class ChainCannon : public Gun {
 private:
  Spray spray;
  double slope;
  double intercept;
  Uint32 last_shot_time;
  bool triggered;

  double linear_func(double x);

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
