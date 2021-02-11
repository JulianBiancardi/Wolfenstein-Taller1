#ifndef ROCKET_LAUNCHER_H
#define ROCKET_LAUNCHER_H

#include "gun.h"

class RocketLauncher : public Gun {
 private:
  bool triggered;

  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  RocketLauncher();
  ~RocketLauncher();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger() override;
};

#endif
