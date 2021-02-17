#include "rocket_launcher.h"

#include "../../../../common/src/main/ids/gun_ids.h"

Hit RocketLauncher::shoot(
    Object& player, int& current_bullets, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, true));
}

RocketLauncher::RocketLauncher() : Gun(0, 0) {}

RocketLauncher::~RocketLauncher() = default;

Hit RocketLauncher::trigger(
    Object& player, int& current_bullets, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  if (triggered || current_bullets == 0) {
    return std::move(Hit(ROCKET_LAUNCHER_ID, 0, 0, false));
  } else {
    triggered = true;
    return std::move(shoot(player, current_bullets, map, players));
  }
}

void RocketLauncher::untrigger() { triggered = false; }

Image* RocketLauncher::get_image(ResourceManager& resource_manager) {}

SDL_Rect* RocketLauncher::get_slice(void* extra) {
  // TODO OPTIMIZE THIS
  Image* image = (Image*)extra;
  int frame_width = (image->get_width() - 4 * PIXEL) / 5;
  int frame_height = image->get_height();

  Uint32 sprite_x;
  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 1000;

  if (!triggered) {
    sprite_x = 0;
  } else {
    sprite_x = seconds % 5;
  }

  slice = {(sprite_x * (frame_width + PIXEL)), 0, frame_width, frame_height};
  return &slice;
}
