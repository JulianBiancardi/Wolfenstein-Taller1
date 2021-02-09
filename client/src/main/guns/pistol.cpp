#include "pistol.h"

#include <algorithm>
#include <cmath>
#include <iostream>  // TODO delete
#include <limits>
#include <utility>

#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/ids/gun_ids.h"
#include "../casting/ray_casting.h"

#define COS_MOD 3

Pistol::Pistol()
    : generator(),
      distribution(1, CL::bullet_max_dmg),
      spray(CL::pistol_spray, CL::pistol_std_dev),
      Gun(0, CL::pistol_range),
      triggered(false) {
  slope = 1 / (min_range - max_range);
  intercept = -slope * max_range;
}

Hit Pistol::shoot(Object& player, int& current_bullets, BaseMap& map,
                  const std::vector<std::shared_ptr<Object>>& objects) {
  Ray bullet(player.get_position(), player.get_angle() + spray());

  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  std::shared_ptr<Object> closest_obj(nullptr);
  double closest_obj_dist = std::numeric_limits<double>::infinity();
  double closest_obj_angle = std::numeric_limits<double>::quiet_NaN();

  std::vector<std::shared_ptr<Object>>::const_iterator iter;

  for (iter = objects.begin(); iter != objects.end(); iter++) {
    std::shared_ptr<Object> object = *iter;
    // TODO Consider: if (!object.is_solid()) {continue;}
    double object_distance =
        object->get_position().distance_from(bullet.get_origin());
    if (object_distance >= wall_distance ||
        object_distance >= closest_obj_dist || object_distance >= max_range ||
        object_distance == 0) {
      continue;
    }

    // As a decision of implementation design, solid objects have same radius
    // TODO Change number 0.5 to use ConfigLoader and use the actual size of
    // things, or pick a better number later.
    double half_angular_diameter = atan(0.5 / object_distance);
    double object_angle = bullet.get_origin().angle_to(object->get_position());

    double left_angle = Angle::normalize(object_angle + half_angular_diameter);

    double right_angle = Angle::normalize(object_angle - half_angular_diameter);

    // Check if bullet angle is between object angular diameter
    double rel_angle = std::fmod(
        std::fmod(left_angle - right_angle, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
    if (rel_angle >= M_PI) {
      std::swap(left_angle, right_angle);
    }

    bool hit = false;
    double bullet_angle = bullet.get_angle();
    if (right_angle <= left_angle) {
      hit = bullet_angle >= right_angle && bullet_angle <= left_angle;
    } else {
      hit = bullet_angle >= right_angle || bullet_angle <= left_angle;
    }

    if (hit) {
      closest_obj = object;
      closest_obj_dist = object_distance;
      closest_obj_angle = object_angle;
    }
  }

  if (closest_obj_dist != std::numeric_limits<double>::infinity()) {
    double base_damage = distribution(generator);
    double dist_modifier =
        std::max(0.0, std::min(1.0, linear_func(closest_obj_dist)));
    double angle_modifier =
        std::fabs(std::cos((closest_obj_angle - bullet.get_angle()) *
                           (M_PI / (COS_MOD * CL::pistol_spray))));
    double damage = base_damage * dist_modifier * angle_modifier;

    return std::move(Hit(PISTOL_ID, closest_obj->get_id(), damage, true));
  }
  return std::move(Hit(PISTOL_ID, 0, 0, true));
}

Hit Pistol::trigger(Object& player, int& current_bullets, BaseMap& map,
                    const std::vector<std::shared_ptr<Object>>& objects) {
  if (triggered || current_bullets == 0) {
    return std::move(Hit(PISTOL_ID, 0, 0, false));
  } else {
    triggered = true;
    return std::move(shoot(player, current_bullets, map, objects));
  }
}

void Pistol::untrigger() { triggered = false; }

double Pistol::linear_func(double x) { return slope * x + intercept; }

Pistol::~Pistol() {}