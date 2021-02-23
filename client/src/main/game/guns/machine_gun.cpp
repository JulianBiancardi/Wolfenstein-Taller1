#include "machine_gun.h"

#include <SDL2/SDL.h>

#include <cmath>
#include <limits>
#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"
#include "../rendering/ray_casting.h"

#define COS_MOD 3

MachineGun::MachineGun(unsigned int resource_id)
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::machine_gun_spray, CL::machine_gun_std_dev),
      Gun(0, CL::machine_gun_range, resource_id),
      last_shot_time(0),
      last_burst_time(0),
      bullet_count(0) {}

MachineGun::~MachineGun() {}

Hit MachineGun::shoot(Object& player, BaseMap& map,
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

Hit MachineGun::update(
    Object& player, bool trigger, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  // Not in burst, not triggered
  if (bullet_count == 0 && !trigger) {
    state.update(false);
    return std::move(Hit(MACHINE_GUN_ID, 0, 0, false));
  }

  long now = SDL_GetTicks();
  // Not in burst, triggered
  if (bullet_count == 0 && trigger &&
      now - last_burst_time > CL::machine_gun_burst_frequency) {
    bullet_count++;
    last_shot_time = now;
    last_burst_time = now;
    state.update(true);
    return std::move(shoot(player, map, players));
  }

  // In burst
  if (bullet_count > 0 &&
      now - last_shot_time > CL::machine_gun_shot_frequency) {
    bullet_count++;
    last_shot_time = now;
    if (bullet_count == 5) {
      bullet_count = 0;
    }
    state.update(true);
    return std::move(shoot(player, map, players));
  }

  state.update(false);
  return std::move(Hit(MACHINE_GUN_ID, 0, 0, false));
}

double MachineGun::linear_func(double x) { return slope * x + intercept; }

SDL_Rect* MachineGun::get_slice(void* extra) {
  state.set_slice(slice);
  return &slice;
}
