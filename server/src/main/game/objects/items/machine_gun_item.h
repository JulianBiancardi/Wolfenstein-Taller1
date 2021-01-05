#ifndef MACHINE_GUN_ITEM_H
#define MACHINE_GUN_ITEM_H

#include "item.h"

class MachineGunItem : public Item {
 public:
  MachineGunItem(Point center, int id);
  void use(Player& user) override;
  Item* copy() override;
  bool can_be_used_by(Player& whom) override;
  void remove() override;

 private:
  static int health_recovered;
};

#endif
