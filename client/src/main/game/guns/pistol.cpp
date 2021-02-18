#include "pistol.h"

#include <cmath>
#include <limits>
#include <utility>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/ids/gun_ids.h"
#include "../entities/player.h"
#include "../rendering/ray_casting.h"

#define COS_MOD 3

Pistol::Pistol()
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::pistol_spray, CL::pistol_std_dev),
      Gun(0, CL::pistol_range),
      shot(false) {
  slope = 1 / (min_range - max_range);
  intercept = -slope * max_range;
}

Pistol::~Pistol() {}

Hit Pistol::shoot(Object& player, BaseMap& map,
                  std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  Ray bullet(player.get_position(), player.get_angle() + spray());

  std::shared_ptr<IdentifiableObject> target = trayectory(bullet, map, players);

  if (target == nullptr) {
    return std::move(Hit(PISTOL_ID, 0, 0, true));
  }

  double target_dist =
      target->get_position().distance_from(player.get_position());
  double target_angle =
      bullet.get_origin().angle_to(target->get_position()) - bullet.get_angle();

  double base_dmg = distribution(generator);
  double dist_modifier = std::max(0.0, std::min(1.0, linear_func(target_dist)));
  double angle_modifier =
      std::fabs(std::cos(target_angle * (M_PI / (3 * CL::pistol_spray))));
  double damage = base_dmg * dist_modifier * angle_modifier;

  return std::move(Hit(PISTOL_ID, target->get_id(), damage, true));
}

Hit Pistol::update(Object& player, bool trigger, BaseMap& map,
                   std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  if (!trigger) {
    shot = false;
    state.update(false);
    return std::move(Hit(PISTOL_ID, 0, 0, false));
  }

  if (shot) {
    state.update(false);
    return std::move(Hit(PISTOL_ID, 0, 0, false));
  }

  shot = true;
  state.update(true);
  return std::move(shoot(player, map, players));
}

double Pistol::linear_func(double x) { return slope * x + intercept; }

Image* Pistol::get_image(ResourceManager& resource_manager) {}

SDL_Rect* Pistol::get_slice(void* extra) {
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

  slice = {(sprite_x * (frame_width + PIXEL)), 0, frame_width, frame_height};*/
  return &slice;
}
