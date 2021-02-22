#include "horizontal_door.h"

HorizontalDoor::HorizontalDoor(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

HorizontalDoor::~HorizontalDoor() {}

Point HorizontalDoor::get_collision_point(double x, double y, double angle) {
  if (angle == 0) {
    // Not hittable
  } else if (angle > 0 && angle < M_PI_2) {
    double dx = std::fmod(x, 1);
    if (tan(angle) * (1 - dx) < 0.5) {
      // Not hitting door
    }
    return Point(x + 0.5 / tan(angle), y - 0.5);
  } else if (angle == M_PI_2) {
    return Point(x, y - 0.5);
  } else if (angle > M_PI_2 && angle < M_PI) {
    double dx = std::fmod(x, 1);
    if (tan(angle) * dx < 0.5) {
      // Not hitting door
    }
    return Point(x - 0.5 / tan(angle), y - 0.5);
  } else if (angle == M_PI) {
    // Not hittable
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    double dx = std::fmod(x, 1);
    if (tan(angle) * dx < 0.5) {
      // Not hitting door
    }
    return Point(x - 0.5 / tan(angle), y + 0.5);
  } else if (angle == 3 * M_PI_2) {
    return Point(x, y + 0.5);
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    double dx = std::fmod(x, 1);
    if (tan(angle) * (1 - dx) < 0.5) {
      // Not hitting door
    }
    return Point(x + 0.5 / tan(angle), y + 0.5);
  } else {
    throw 1;
  }
}

bool HorizontalDoor::is_open_at(const Point& point) {
  return state.is_open_by(std::fmod(point.getX(), 1));
}
