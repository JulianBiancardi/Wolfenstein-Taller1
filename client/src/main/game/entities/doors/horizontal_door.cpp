#include "horizontal_door.h"

HorizontalDoor::HorizontalDoor(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

HorizontalDoor::~HorizontalDoor() {}

bool HorizontalDoor::update_collision(Collision& collision, double angle) {
  double tg = fabs(tan(angle));
  double x = collision.get_collision_point().getX();
  double y = collision.get_collision_point().getY();
  if (angle > 0 && angle < M_PI_2) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * (1 - dx);
    if (delta_y < 0.5) {  // Hitting side
      return false;
    }

    new_collision_point = Point(x + 0.5 / tg, y - 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle == M_PI_2) {
    Point new_collision_point(x, y - 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not hitting door
      return false;
    }
    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > M_PI_2 && angle < M_PI) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * dx;
    if (delta_y < 0.5) {  // Hitting side
      return false;
    }

    new_collision_point = Point(x - 0.5 / tg, y - 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * dx;
    if (delta_y < 0.5) {  // Hitting side
      return false;
    }

    new_collision_point = Point(x - 0.5 / tg, y + 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle == 3 * M_PI_2) {
    Point new_collision_point(x, y + 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * (1 - dx);
    if (delta_y < 0.5) {  // Hitting side
      return false;
    }

    new_collision_point = Point(x + 0.5 / tg, y + 0.5);
    if (state.is_open_by(
            std::fmod(new_collision_point.getX(), 1))) {  // Not Hitting door
      return false;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    return true;
  }
  return false;
}

SDL_Rect* HorizontalDoor::get_slice(void* extra) {
  slice.x = (int)(state.get_openness());
  return &slice;
}