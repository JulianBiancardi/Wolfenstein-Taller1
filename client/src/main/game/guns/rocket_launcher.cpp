#include "rocket_launcher.h"

#include "../../../../common/src/main/ids/gun_ids.h"

Hit RocketLauncher::shoot(
    Object& player, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, true));
}

RocketLauncher::RocketLauncher() : Gun(0, 0) {}

RocketLauncher::~RocketLauncher() {}

Hit RocketLauncher::update(
    Object& player, bool trigger, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  if (!trigger) {
    shot = false;
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  }

  if (shot) {
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  }

  shot = true;
  return std::move(shoot(player, map, players));
}
