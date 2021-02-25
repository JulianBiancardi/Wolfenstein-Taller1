#include "rocket_launcher_item.h"

#include "../../../../../../common/src/main/ids/gun_ids.h"

RocketLauncherItem::RocketLauncherItem(const Point& center, unsigned int id)
    : Item(center, id) {}

void RocketLauncherItem::use(Player& user) { user.add_gun(ROCKET_LAUNCHER_ID); }

bool RocketLauncherItem::can_be_used_by(const Player& whom) {
  return !whom.has_gun(ROCKET_LAUNCHER_ID);
}
