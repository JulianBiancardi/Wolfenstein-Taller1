#include "knife.h"

#include <cmath>
#include <limits>
#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../rendering/ray_casting.h"

Knife::Knife()
    : Gun(0, CL::knife_range),
      generator(),
      distribution(1, CL::bullet_max_dmg) {}

Hit Knife::shoot(Object& player, BaseMap& map,
                 std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Ray bullet(player.get_position(), player.get_angle());

  std::shared_ptr<IdentifiableObject> target = trayectory(bullet, map, players);

  if (target == nullptr) {
    return std::move(Hit(KNIFE_ID, 0, 0, true));
  }

  double damage = distribution(generator);

  return std::move(Hit(KNIFE_ID, target->get_id(), damage, true));
}

Hit Knife::update(Object& player, bool trigger, BaseMap& map,
                  std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  if (!trigger) {
    shot = false;
    state.update(false);
    return std::move(Hit(KNIFE_ID, 0, 0, false));
  }

  if (shot) {
    state.update(false);
    return std::move(Hit(KNIFE_ID, 0, 0, false));
  }

  shot = true;
  state.update(true);
  return std::move(shoot(player, map, players));
}

Image* Knife::get_image(ResourceManager& resource_manager) {}

SDL_Rect* Knife::get_slice(void* extra) {
  // TODO OPTIMIZE THIS
  /*
  Image* image = (Image*)extra;
  int frame_width = (image->get_width() - 4 * PIXEL) / 5;
  int frame_height = image->get_height();

  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 10;

  if (animation == stop) {
    sprite_x = 0;
  } else if (animation == play) {
    sprite_x++;
    if (sprite_x == 4) {
      animation = stop;
    }
  }
  sprite_x = 0;
  slice = {(0 * (frame_width + PIXEL)), 0, frame_width, frame_height};
  */
  return &slice;
}
