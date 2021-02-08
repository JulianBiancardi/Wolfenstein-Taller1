#ifndef KNIFE_H
#define KNIFE_H

#include "gun.h"

class Knife : public Gun {
 public:
  Knife();
  Hit shoot(Object& player, int& current_bullets, BaseMap& map,
            const std::vector<Object*>& objects) override;

 private:
  const static int range;
  const static int bullet_required = 0;
};

#endif
