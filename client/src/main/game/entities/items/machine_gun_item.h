#ifndef MACHINE_GUN_ITEM_H
#define MACHINE_GUN_ITEM_H

#include "item.h"

class MachineGunItem : public Item {
 private:
 public:
  MachineGunItem(const Ray& position, unsigned int resource_id,
                 unsigned int id);
  ~MachineGunItem();

  void use_on(Player& player);
};

#endif
