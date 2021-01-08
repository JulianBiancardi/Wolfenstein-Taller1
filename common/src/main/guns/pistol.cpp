#include "pistol.h"

Pistol::Pistol() {
  //    bullet_required =
  //    ConfigLoader::get_init_configs().pistol_bullet_required; base_precision
  //    = ConfigLoader::get_init_configs().pistol_base_precision;
}

int Gun::shoot(Player& player, int& current_bullets, Map& map) {
  /*// Randomizo el daño con random
  std::random_device rd;     // Creo la semilla (toma info aleatoria del SO)
  std::mt19937_64 mt(rd());  // Genero un valor pseudo-aleatorio de 64 bits.
  std::uniform_int_distribution<int> damage_dist(1, 10);

  return damage_dist(mt);
  // shooter.receive_damage(damage_dist(mt));*/

  double angle = player.get_position().get_angle();
  Ray bullet = player.get_position();  // TODO Make some probabilistic shot
  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  std::vector<Object> objects = map.get_objects();
  // TODO Sort objects from closest to farthest, to only hit closest.
  std::vector<Object>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    Object& object = *iter;
    // TODO Consider: if (!object.is_solid()) {continue;}
    double object_distance =
        object.get_position().distance_from(bullet.get_origin());
    // This can be used to limit weapon range
    if (object_distance >= wall_distance) {
      continue;
    }

    // As a decision of implementation design, solid objects have same radius
    // TODO Change number 1 to use ConfigLoader and use the actual size of
    // things.
    double half_angular_diameter = atan(1 / object_distance);
    double object_angle = object.get_position().angle_to(bullet.get_origin());

    double left_angle = object_angle + half_angular_diameter;
    if (left_angle > 2 * M_PI) {
      left_angle -= 2 * M_PI;
    }

    double right_angle = object_angle - half_angular_diameter;
    if (right_angle < 0) {
      right_angle += 2 * M_PI;
    }

    // Check if bullet angle is between object angular diameter
    double rel_angle =
        std::fmod(std::fmod(left_angle - right_angle, 360) + 360, 360);
    if (rel_angle >= 180) {
      std::swap(left_angle, right_angle);
    }

    bool hit = false;
    double bullet_angle = bullet.get_angle();
    if (right_angle <= left_angle) {
      hit = bullet_angle >= right_angle && bullet_angle <= left_angle;
    } else {
      hit = bullet_angle >= right_angle || bullet_angle <= left_angle;
    }
    // TODO We know we hit the object. Proceed with whatever is necessary.
  }
}
