#include "vertical_door.h"

#include "../../../../../common/src/main/utils/point.h"

VerticalDoor::VerticalDoor(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

VerticalDoor::~VerticalDoor() {}

bool VerticalDoor::update_collision(Collision& collision, double angle) {
  double tg = fabs(tan(angle));
  double x = collision.get_collision_point().getX();
  double y = collision.get_collision_point().getY();
  if (angle == 0) {
    Point new_collision_point(x + 0.5, y);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > 0 && angle < M_PI_2) {
    double dy = std::fmod(y, 1);
    double delta_x = dy / tg;
    if (delta_x < 0.5) {  // Hitting side
      return false;
    }

    Point new_collision_point(x + 0.5, y - 0.5 * tg);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > M_PI_2 && angle < M_PI) {
    double dy = std::fmod(y, 1);
    double delta_x = dy / tg;
    if (delta_x < 0.5) {  // Hitting side
      return false;
    }

    Point new_collision_point(x - 0.5, y - 0.5 * tg);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle == M_PI) {
    Point new_collision_point(x - 0.5, y);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    double dy = std::fmod(y, 1);
    double delta_x = (1 - dy) / tg;
    if (delta_x < 0.5) {  // Hitting side
      return false;
    }

    Point new_collision_point(x - 0.5, y + 0.5 * tg);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    double dy = std::fmod(y, 1);
    double delta_x = (1 - dy) / tg;
    if (delta_x < 0.5) {  // Hitting side
      return false;
    }

    Point new_collision_point = Point(x + 0.5, y + 0.5 * tg);
    if (state.is_open_by(
            std::fmod(new_collision_point.getY(), 1))) {  // Not Hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else {
    return false;
  }
}
