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

Image* RocketLauncher::get_image(ResourceManager& resource_manager) {}

SDL_Rect* RocketLauncher::get_slice(void* extra) {
  /*
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

  slice = {(sprite_x * (frame_width + PIXEL)), 0, frame_width, frame_height};*/
  return &slice;
}
