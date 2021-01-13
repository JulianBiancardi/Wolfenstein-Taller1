#include "moveable.h"
#include "../../../../common/src/main/config_loader.h"

Moveable::Moveable(Point origin, double angle, int id)
    : Identifiable(id),
      Object(origin,
             angle,
             new Circle_mask(ConfigLoader::player_mask_radio,
                             position.get_ref_origin())) {}

Moveable::Moveable(Ray position, int id)
    : Identifiable(id),
      Object(position,
             new Circle_mask(ConfigLoader::player_mask_radio,
                             position.get_ref_origin())) {}

Moveable::Moveable(double x, double y, double angle, int id)
    : Identifiable(id),
      Object(Point(x, y),
             angle,
             new Circle_mask(ConfigLoader::player_mask_radio,
                             position.get_ref_origin())) {}

Moveable::Moveable(const Moveable& other)
    : Identifiable(other.id),
      Object(other.position,
             new Circle_mask(ConfigLoader::player_mask_radio,
                             position.get_ref_origin())) {}

Point Moveable::collision_mask_bound(const Point& next_position) {
  double angle = position.get_origin().angle_to(next_position);

  double front_x =
      next_position.getX() + cos(angle) * ((Circle_mask*) mask)->get_radio();
  double front_y =
      next_position.getY() + sin(angle) * ((Circle_mask*) mask)->get_radio();

  return Point(front_x, front_y);
}

// TODO Change position in Object, not from Moveable.
void Moveable::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
}

bool Moveable::operator!=(const Moveable& other) const {
  return (this != &other);
}
