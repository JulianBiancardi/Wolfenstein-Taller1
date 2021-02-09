#include "moveable.h"

#include <cmath>

#include "collisions/circle_mask.h"

Moveable::Moveable(Point origin, double angle, double speed,
                   double rotation_speed, double radius)
    : Object(origin, angle, new CircleMask(radius, position.get_ref_origin())),
      speed(speed),
      rotation_speed(rotation_speed) {}

Moveable::Moveable(Point origin, double angle, double speed,
                   double rotation_speed, double radius, unsigned int id)
    : Object(origin, angle, new CircleMask(radius, position.get_ref_origin()),
             id),
      speed(speed),
      rotation_speed(rotation_speed) {}

Moveable::Moveable(Ray position, double speed, double rotation_speed,
                   double radius)
    : Object(position, new CircleMask(radius, position.get_ref_origin())),
      speed(speed),
      rotation_speed(rotation_speed) {}

Moveable::Moveable(double x, double y, double angle, double speed,
                   double rotation_speed, double radius)
    : Object(Point(x, y), angle,
             new CircleMask(radius, position.get_ref_origin())),
      speed(speed),
      rotation_speed(rotation_speed) {}

Moveable::Moveable(const Moveable& other)
    : Object(other.position,
             new CircleMask(((CircleMask*)other.mask)->get_radius(),
                            position.get_ref_origin()),
             other.id),
      speed(other.speed),
      rotation_speed(other.rotation_speed) {}

Moveable::~Moveable() = default;

Point Moveable::next_position(double direction_angle) {
  double movement_angle = position.get_angle() + direction_angle;

  double next_x = position.get_origin().getX() + cos(movement_angle) * speed;
  double next_y = position.get_origin().getY() - sin(movement_angle) * speed;

  return Point(next_x, next_y);
}

Point Moveable::next_position(int direction) {
  switch (direction) {
    case UP:
      return next_position(0.0);
    case UP_LEFT:
      return next_position(M_PI / 4);
    case UP_RIGHT:
      return next_position(7 * M_PI / 4);
    case LEFT:
      return next_position(M_PI / 2);
    case RIGHT:
      return next_position(3 * M_PI / 2);
    case DOWN_LEFT:
      return next_position(3 * M_PI / 4);
    case DOWN_RIGHT:
      return next_position(5 * M_PI / 4);
    case DOWN:
      return next_position(M_PI);
    default:  // Do nothing
      break;
  }
}

void Moveable::rotate(int direction) {
  if (direction == LEFT_ROTATION) {
    position =
        Ray(position.get_ref_origin(), position.get_angle() + rotation_speed);
  } else {
    position =
        Ray(position.get_ref_origin(), position.get_angle() - rotation_speed);
  }
}

Point Moveable::collision_mask_bound(const Point& next_position) {
  double angle = position.get_origin().angle_to(next_position);

  double front_x =
      next_position.getX() + cos(angle) * ((CircleMask*)mask)->get_radius();
  double front_y =
      next_position.getY() - sin(angle) * ((CircleMask*)mask)->get_radius();

  return Point(front_x, front_y);
}

void Moveable::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
}

// TODO Check this!
bool Moveable::operator!=(const Moveable& other) const {
  return (this != &other);
}
