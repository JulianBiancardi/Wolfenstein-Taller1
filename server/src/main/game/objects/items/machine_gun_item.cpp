#include "machine_gun_item.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"
#include "../../../../common/src/main/ids/gun_ids.h"

MachineGunItem::MachineGunItem(const Point& center, unsigned int id)
    : Item(center, id) {}

void MachineGunItem::use(Player& user) { user.add_gun(MACHINE_GUN_ID); }

bool MachineGunItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(MACHINE_GUN_ID);
}

Item* MachineGunItem::copy() {
  return new MachineGunItem(position.get_origin(), id);
}

Packet MachineGunItem::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, MACHINE_GUN,
                     (int) position.get_origin().getX(),
                     (int) position.get_origin().getY());
  return std::move(Packet(size, data));
}
