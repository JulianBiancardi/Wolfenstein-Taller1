#include "machine_gun.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <limits>
#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../rendering/ray_casting.h"

#define COS_MOD 3

MachineGun::MachineGun()
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::machine_gun_spray, CL::machine_gun_std_dev),
      Gun(0, CL::machine_gun_range),
      last_shot_time(0),
      triggered(false) {}

Hit MachineGun::shoot(Object& player, int& current_bullets, BaseMap& map,
                      std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Ray bullet(player.get_position(), player.get_angle() + spray());

  std::shared_ptr<IdentifiableObject> target = trayectory(bullet, map, players);

  if (target == nullptr) {
    return std::move(Hit(MACHINE_GUN_ID, 0, 0, true));
  }

  double target_dist =
      target->get_position().distance_from(player.get_position());
  double target_angle =
      bullet.get_origin().angle_to(target->get_position()) - bullet.get_angle();

  double base_dmg = distribution(generator);
  double dist_modifier = std::max(0.0, std::min(1.0, linear_func(target_dist)));
  double angle_modifier =
      std::fabs(std::cos(target_angle * (M_PI / (3 * CL::machine_gun_spray))));
  double damage = base_dmg * dist_modifier * angle_modifier;

  return std::move(Hit(MACHINE_GUN_ID, target->get_id(), damage, true));
}

Hit MachineGun::trigger(
    Object& player, int& current_bullets, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Uint32 now_time = SDL_GetTicks();
  if (current_bullets == 0 ||
      (now_time - last_shot_time) < CL::machine_gun_frecuency) {
    return std::move(Hit(MACHINE_GUN_ID, 0, 0, false));
  } else {
    last_shot_time = SDL_GetTicks();
    return std::move(shoot(player, current_bullets, map, players));
  }
}

double MachineGun::linear_func(double x) { return slope * x + intercept; }

void MachineGun::untrigger() {}

MachineGun::~MachineGun() {}

Image* MachineGun::get_image(ResourceManager& resource_manager) {}

SDL_Rect* MachineGun::get_slice(void* extra) {
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