#ifndef ROCKET_LAUNCHER_ITEM_H
#define ROCKET_LAUNCHER_ITEM_H

#include "item.h"

class RocketLauncherItem : public Item {
 private:
 public:
  RocketLauncherItem(const Ray& position, unsigned int resource_id,
                     unsigned int id);
  ~RocketLauncherItem();

  void use_on(Player& player);
};

#endif
