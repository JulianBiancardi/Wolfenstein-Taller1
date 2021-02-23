#include "machine_gun_item.h"

#include "../../../../common/src/main/ids/gun_ids.h"

MachineGunItem::MachineGunItem(const Point& center, unsigned int id)
    : Item(center, id) {}

void MachineGunItem::use(Player& user) { user.add_gun(MACHINE_GUN_ID); }

bool MachineGunItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(MACHINE_GUN_ID);
}
