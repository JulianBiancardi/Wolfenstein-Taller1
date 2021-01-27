#include "rocket_launcher_item.h"

#include "../../../../common/src/main/ids/gun_ids.h"

RocketLauncherItem::RocketLauncherItem(Point center) : Item(center) {}

RocketLauncherItem::RocketLauncherItem(Point center, int id)
    : Item(center, id) {}

void RocketLauncherItem::use(Player& user) { user.add_gun(ROCKET_LAUNCHER_ID); }

Item* RocketLauncherItem::copy() {
  return new RocketLauncherItem(position.get_origin(), id);
}

bool RocketLauncherItem::can_be_used_by(Player& whom) {
  return !whom.has_gun(ROCKET_LAUNCHER_ID);
}
