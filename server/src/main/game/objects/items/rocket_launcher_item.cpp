#include "rocket_launcher_item.h"

#include <utility>

#include "../../../../../../common/src/main/ids/map_ids.h"
#include "../../../../common/src/main/ids/gun_ids.h"

RocketLauncherItem::RocketLauncherItem(const Point& center, int id)
    : Item(center, id) {}

RocketLauncherItem::RocketLauncherItem(const Point& center) : Item(center) {}

void RocketLauncherItem::use(Player& user) { user.add_gun(ROCKET_LAUNCHER_ID); }

bool RocketLauncherItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(ROCKET_LAUNCHER_ID);
}

Item* RocketLauncherItem::copy() {
  return new RocketLauncherItem(position.get_origin(), id);
}

Packet RocketLauncherItem::get_add_item_packet() {
  unsigned char data[ADD_ITEM_SIZE];
  size_t size = pack(data, "CICCC", ADD_ITEM, id, BAZOOKA,
                     (int)position.get_origin().getX(),
                     (int)position.get_origin().getY());
  return std::move(Packet(size, data));
}
