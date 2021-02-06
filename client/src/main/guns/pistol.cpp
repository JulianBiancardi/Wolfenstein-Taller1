#include "pistol.h"

#include <algorithm>
#include <cmath>
#include <iostream>  // TODO delete
#include <limits>
#include <utility>

#include "../casting/ray_casting.h"

Pistol::Pistol() : spray(0.17453, 0.1), Gun(2, 20) {
  slope = 1 / (min_range - max_range);
  intercept = -slope * max_range;
  //    bullet_required =
  //    ConfigLoader::get_init_configs().pistol_bullet_required; base_precision
  //    = ConfigLoader::get_init_configs().pistol_base_precision;
}

Hit Pistol::shoot(Object& player, int& current_bullets, BaseMap& map,
                  const std::vector<Object*>& objects) {
  Ray bullet(player.get_position(), player.get_angle() + spray());

  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  Object* closest_obj = nullptr;
  double closest_obj_dist = std::numeric_limits<double>::infinity();
  double closest_obj_angle = std::numeric_limits<double>::quiet_NaN();

  std::vector<Object*>::const_iterator iter;

  for (iter = objects.begin(); iter != objects.end(); iter++) {
    Object* object = *iter;
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
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1, 10);
    double base_damage = distribution(generator);
    double dist_modifier =
        std::max(0.0, std::min(1.0, linear_func(closest_obj_dist)));
    double angle_modifier = std::cos(closest_obj_angle);
    double damage = base_damage * dist_modifier * angle_modifier;

    return std::move(Hit(closest_obj->get_id(), damage));
  }
  return std::move(Hit(-1, 0));
}

double Pistol::linear_func(double x) { return slope * x + intercept; }

Pistol::~Pistol() {}