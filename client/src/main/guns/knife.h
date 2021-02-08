#ifndef KNIFE_H
#define KNIFE_H

#include "gun.h"

class Knife : public Gun {
 private:
  bool triggered;
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<std::shared_ptr<Object>>& objects) override;

 public:
  Knife();

  Hit trigger(Object& player, int& current_bullets, BaseMap& map,
              const std::vector<std::shared_ptr<Object>>& objects) override;
  void untrigger();
};

#endif
