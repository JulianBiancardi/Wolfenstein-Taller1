#include "vertical_door.h"

VerticalDoor::VerticalDoor(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

VerticalDoor::~VerticalDoor() {}

/*
Point VerticalDoor::get_collision_point(double x, double y, double angle) {
  if (angle == 0) {
    return Point(x + 0.5, y);
  } else if (angle > 0 && angle < M_PI_2) {
    double dy = std::fmod(y, 1);
    if (tan(angle) * dy < 0.5) {
      // Not hitting door
    }
    return Point(x + 0.5, y - 0.5 / tan(angle));
  } else if (angle == M_PI_2) {
    // not hittable
  } else if (angle > M_PI_2 && angle < M_PI) {
    double dy = std::fmod(y, 1);
    if (tan(angle) * dy < 0.5) {
      // Not hitting door
    }
    return Point(x - 0.5, y - 0.5 / tan(angle));
  } else if (angle == M_PI) {
    return Point(x - 0.5, y);
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    double dy = std::fmod(y, 1);
    if (tan(angle) * (1 - dy) < 0.5) {
      // Not hitting door
    }
    return Point(x - 0.5, y + 0.5 / tan(angle));
  } else if (angle == 3 * M_PI_2) {
    // Not hittable
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    double dy = std::fmod(y, 1);
    if (tan(angle) * (1 - dy) < 0.5) {
      // Not hitting door
    }
    return Point(x + 0.5, y + 0.5 / tan(angle));
  } else {
    throw 1;
  }
}*/