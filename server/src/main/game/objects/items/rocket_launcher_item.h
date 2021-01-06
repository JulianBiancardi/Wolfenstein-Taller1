#ifndef ROCKET_LAUNCHER_ITEM_H
#define ROCKET_LAUNCHER_ITEM_H

#include "item.h"

class RocketLauncherItem : public Item {
 public:
  RocketLauncherItem(Point center, int id);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  static int health_recovered;
};

#endif