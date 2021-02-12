#include "chain_cannon.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"

#define COS_MOD 3

ChainCannon::ChainCannon()
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::chain_cannon_spray, CL::chain_cannon_std_dev),
      Gun(0, CL::chain_cannon_range),
      last_shot_time(0),
      triggered(false) {}

Hit ChainCannon::shoot(
    Object& player, int& current_bullets, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Ray bullet(player.get_position(), player.get_angle() + spray());

  std::shared_ptr<IdentifiableObject> target = trayectory(bullet, map, players);

  if (target == nullptr) {
    return std::move(Hit(CHAIN_CANNON_ID, 0, 0, true));
  }

  double target_dist =
      target->get_position().distance_from(player.get_position());
  double target_angle =
      bullet.get_origin().angle_to(target->get_position()) - bullet.get_angle();

  double base_dmg = distribution(generator);
  double dist_modifier = std::max(0.0, std::min(1.0, linear_func(target_dist)));
  double angle_modifier =
      std::fabs(std::cos(target_angle * (M_PI / (3 * CL::chain_cannon_spray))));
  double damage = base_dmg * dist_modifier * angle_modifier;

  return std::move(Hit(CHAIN_CANNON_ID, target->get_id(), damage, true));
}

Hit ChainCannon::trigger(
    Object& player, int& current_bullets, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Uint32 now_time = SDL_GetTicks();
  if (current_bullets == 0 ||
      (now_time - last_shot_time) < CL::machine_gun_frecuency) {
    return std::move(Hit(CHAIN_CANNON_ID, 0, 0, false));
  } else {
    last_shot_time = SDL_GetTicks();
    return std::move(shoot(player, current_bullets, map, players));
  }
}

double ChainCannon::linear_func(double x) { return slope * x + intercept; }

void ChainCannon::untrigger() {}

ChainCannon::~ChainCannon() {}