#include "chain_cannon.h"

#include <SDL2/SDL.h>

#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>

#include "../../../../../common/src/main/config_loader.h"
#include "../../../../../common/src/main/ids/gun_ids.h"

ChainCannon::ChainCannon()
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::chain_cannon_spray, CL::chain_cannon_std_dev),
      Gun(0, CL::chain_cannon_range),
      last_shot_time(0),
      triggered(false) {}

ChainCannon::~ChainCannon() {}

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
  if (current_bullets == 0) {
    animation = stop;
    return std::move(Hit(CHAIN_CANNON_ID, 0, 0, false));
  }

  Uint32 now_time = SDL_GetTicks();
  if ((now_time - last_shot_time) < CL::machine_gun_frecuency) {
    return std::move(Hit(CHAIN_CANNON_ID, 0, 0, false));
  } else {
    last_shot_time = SDL_GetTicks();
    animation = play;
    return std::move(shoot(player, current_bullets, map, players));
  }
}

double ChainCannon::linear_func(double x) { return slope * x + intercept; }

void ChainCannon::untrigger() { sprite_x = 4; }

Image* ChainCannon::get_image(ResourceManager& resource_manager) {}

SDL_Rect* ChainCannon::get_slice(void* extra) {
  // TODO OPTIMIZE THIS
  Image* image = (Image*)extra;
  int frame_width = (image->get_width() - 4 * PIXEL) / 5;
  int frame_height = image->get_height();

  Uint32 ticks = SDL_GetTicks();
  Uint32 seconds = ticks / 1000;

  if (animation == stop) {
    sprite_x = 0;
  } else if (animation == play) {
    if (sprite_x == 4) {
      animation = stop;
    }
    if (sprite_x == 3) {
      sprite_x = 2;
    } else {
      sprite_x++;
    }
  }

  slice = {(sprite_x * (frame_width + PIXEL)), 0, frame_width, frame_height};
  return &slice;
}