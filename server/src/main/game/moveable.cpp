#include "moveable.h"

#include <cmath>

#include "../../../../common/src/main/collisions/circle_mask.h"
#include "../../../../common/src/main/config_loader.h"
#include "../../../../common/src/main/ids/movement_ids.h"

// TODO Use config loader
Moveable::Moveable(Point origin, double angle)
    : Object(origin, angle,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin())),
      pace(CL::player_pace),
      rotation_angle(CL::player_rotation_angle) {}

Moveable::Moveable(Ray position)
    : Object(position, new CircleMask(ConfigLoader::player_mask_radio,
                                      position.get_ref_origin())),
      pace(CL::player_pace),
      rotation_angle(CL::player_rotation_angle) {}

Moveable::Moveable(double x, double y, double angle)
    : Object(Point(x, y), angle,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin())),
      pace(CL::player_pace),
      rotation_angle(CL::player_rotation_angle) {}

Moveable::Moveable(const Moveable& other)
    : Object(other.position,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin()),
             other.id),
      pace(CL::player_pace),
      rotation_angle(CL::player_rotation_angle) {}

Point Moveable::next_position(double direction_angle) {
  double movement_angle = position.get_angle() + direction_angle;

  double next_x = position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y = position.get_origin().getY() - sin(movement_angle) * pace;

  return Point(next_x, next_y);
}

Point Moveable::next_position(int direction) {
  switch (direction) {
    case UP:
      return next_position(0.0);
    case UP_LEFT:
      return next_position(M_PI / 4);
    case LEFT:
      return next_position(M_PI / 2);
    case DOWN_LEFT:
      return next_position(3 * M_PI / 4);
    case DOWN:
      return next_position(M_PI);
    case DOWN_RIGHT:
      return next_position(5 * M_PI / 4);
    case RIGHT:
      return next_position(3 * M_PI / 2);
    case UP_RIGHT:
      return next_position(7 * M_PI / 4);
    default:
      break;
  }
}

void Moveable::rotate(int direction) {
  if (direction == LEFT_ROTATION)
    position =
        Ray(position.get_ref_origin(), position.get_angle() + rotation_angle);
  else
    position =
        Ray(position.get_ref_origin(), position.get_angle() - rotation_angle);
}

Point Moveable::collision_mask_bound(const Point& next_position) {
  double angle = position.get_origin().angle_to(next_position);

  double front_x =
      next_position.getX() + cos(angle) * ((CircleMask*)mask)->get_radius();
  double front_y =
      next_position.getY() - sin(angle) * ((CircleMask*)mask)->get_radius();

  return Point(front_x, front_y);
}

// TODO Change position in Object, not from Moveable.
void Moveable::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
}

bool Moveable::operator!=(const Moveable& other) const {
  return (this != &other);
}
