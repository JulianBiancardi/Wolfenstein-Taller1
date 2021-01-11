#include "rocket_launcher_item.h"

#include "../../../../client/src/main/guns/rocket_launcher.h"

RocketLauncherItem::RocketLauncherItem(Point center, int id)
    : Item(center, id) {}

void RocketLauncherItem::use(Player& user) {
  // user.add_gun(gun);
}

Item* RocketLauncherItem::copy() {
  return new RocketLauncherItem(position.get_origin(), id);
}

bool RocketLauncherItem::can_be_used_by(Player& whom) {
  // return !whom.has_gun(gun);
  return false;
}

void RocketLauncherItem::remove() {}
