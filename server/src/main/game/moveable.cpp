#include "moveable.h"

#include "../../../../common/src/main/collisions/circle_mask.h"
#include "../../../../common/src/main/config_loader.h"

Moveable::Moveable(Point origin, double angle)
    : Object(origin, angle,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin())) {}

Moveable::Moveable(Ray position)
    : Object(position, new CircleMask(ConfigLoader::player_mask_radio,
                                      position.get_ref_origin())) {}

Moveable::Moveable(double x, double y, double angle)
    : Object(Point(x, y), angle,
             new CircleMask(ConfigLoader::player_mask_radio,
                            position.get_ref_origin())) {}

Moveable::Moveable(const Moveable& other)
    : Object(other.position, new CircleMask(ConfigLoader::player_mask_radio,
                                            position.get_ref_origin())) {}

Point Moveable::collision_mask_bound(const Point& next_position) {
  double angle = position.get_origin().angle_to(next_position);

  double front_x =
      next_position.getX() + cos(angle) * ((CircleMask*)mask)->get_radius();
  double front_y =
      next_position.getY() + sin(angle) * ((CircleMask*)mask)->get_radius();

  return Point(front_x, front_y);
}

// TODO Change position in Object, not from Moveable.
void Moveable::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
}

bool Moveable::operator!=(const Moveable& other) const {
  return (this != &other);
}
