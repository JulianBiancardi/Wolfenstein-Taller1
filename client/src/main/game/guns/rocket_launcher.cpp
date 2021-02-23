#include "rocket_launcher.h"

#include "../../../../common/src/main/ids/gun_ids.h"

Hit RocketLauncher::shoot(
    Object& player, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, true));
}

RocketLauncher::RocketLauncher(unsigned int resource_id)
    : Gun(0, 0, resource_id) {}

RocketLauncher::~RocketLauncher() {}

Hit RocketLauncher::update(
    Object& player, bool trigger, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  if (!trigger) {
    shot = false;
    state.update(false);
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  }

  if (shot) {
    state.update(false);
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  }

  shot = true;
  state.update(true);
  return std::move(shoot(player, map, players));
}

SDL_Rect* RocketLauncher::get_slice(void* extra) {
  state.set_slice(slice);
  return &slice;
}
