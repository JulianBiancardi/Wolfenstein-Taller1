#include "gun.h"

#include "../entities/player.h"
#include "../rendering/ray_casting.h"

Gun::Gun(double min_range, double max_range, unsigned int resource_id)
    : min_range(min_range), max_range(max_range), resource_id(resource_id) {}

Gun::~Gun() {}

std::shared_ptr<IdentifiableObject> Gun::trayectory(
    Ray& bullet, BaseMap& map,
    std::vector<std::weak_ptr<IdentifiableObject>>& players) {
  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  std::shared_ptr<IdentifiableObject> closest_obj(nullptr);
  double closest_obj_dist = std::numeric_limits<double>::infinity();

  std::vector<std::weak_ptr<IdentifiableObject>> kept_players;

  std::vector<std::weak_ptr<IdentifiableObject>>::const_iterator iter;
  for (iter = players.begin(); iter != players.end(); iter++) {
    if (iter->expired()) {
      continue;
    }

    kept_players.push_back(*iter);
    std::shared_ptr<IdentifiableObject> object = iter->lock();

    if (std::static_pointer_cast<Player>(object)->is_dead()) {
      continue;
    }

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
    bool hit = false;

    double rel_angle = std::fmod(
        std::fmod(left_angle - right_angle, 2 * M_PI) + 2 * M_PI, 2 * M_PI);
    if (rel_angle >= M_PI) {
      std::swap(left_angle, right_angle);
    }

    double bullet_angle = bullet.get_angle();
    if (right_angle <= left_angle) {
      hit = bullet_angle >= right_angle && bullet_angle <= left_angle;
    } else {
      hit = bullet_angle >= right_angle || bullet_angle <= left_angle;
    }

    if (hit) {
      closest_obj = object;
      closest_obj_dist = object_distance;
    }
  }

  std::swap(kept_players, players);

  return std::move(closest_obj);
}

Image* Gun::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(resource_id);
}
