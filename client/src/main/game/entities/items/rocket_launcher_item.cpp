#include "rocket_launcher_item.h"

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/gun_ids.h"
#include "../../../../../../common/src/main/ids/map_ids.h"

RocketLauncherItem::RocketLauncherItem(const Ray& position,
                                       unsigned int resource_id,
                                       unsigned int id)
    : Item(position, resource_id, id) {}

RocketLauncherItem::~RocketLauncherItem() {}

void RocketLauncherItem::use_on(Player& player) {
  player.add_gun(ROCKET_LAUNCHER_ID);
}