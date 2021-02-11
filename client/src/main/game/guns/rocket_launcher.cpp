#include "rocket_launcher.h"

#include "../../../../../common/src/main/ids/gun_ids.h"

Hit RocketLauncher::shoot(Object& player, int& current_bullets, BaseMap& map,
                          const std::vector<std::shared_ptr<Object>>& objects) {
  return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, true));
}

RocketLauncher::RocketLauncher() : Gun(0, 0) {}

RocketLauncher::~RocketLauncher() = default;

Hit RocketLauncher::trigger(
    Object& player, int& current_bullets, BaseMap& map,
    const std::vector<std::shared_ptr<Object>>& objects) {
  if (triggered || current_bullets == 0) {
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  } else {
    triggered = true;
    return std::move(shoot(player, current_bullets, map, objects));
  }
}

void RocketLauncher::untrigger() { triggered = false; }
