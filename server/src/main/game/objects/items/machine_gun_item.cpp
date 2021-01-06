#include "machine_gun_item.h"

#include "../../guns/machine_gun.h"

MachineGunItem::MachineGunItem(Point center, int id) : Item(center, id) {}

void MachineGunItem::use(Player& user) {
  // user.add_gun(gun);
}

Item* MachineGunItem::copy() {
  return new MachineGunItem(position.get_origin(), id);
}

bool MachineGunItem::can_be_used_by(Player& whom) {
  // return !whom.has_gun(gun);
  return false;
}

void MachineGunItem::remove() {}
