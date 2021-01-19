#include "machine_gun_item.h"
#include "../../../../common/src/main/packets/packet.h"

MachineGunItem::MachineGunItem(Point center) : Item(center) {}

MachineGunItem::MachineGunItem(Point center, int id) : Item(center, id) {}

void MachineGunItem::use(Player& user) {
  user.add_gun(MACHINE_GUN_ID);
}

Item* MachineGunItem::copy() {
  return new MachineGunItem(position.get_origin(), id);
}

bool MachineGunItem::can_be_used_by(Player& whom) {
  return !whom.has_gun(MACHINE_GUN_ID);
}
