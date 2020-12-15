#include "moveable.h"

Moveable::Moveable(Point origin, double angle)
    : angled_position(origin, angle),
      mask(5, angled_position.get_ref_origin()) {} // TODO Use config file

Moveable::Moveable(double x, double y, double angle)
    : angled_position(x, y, angle),
      mask(5, angled_position.get_ref_origin()) {} // TODO Use config file

Moveable::Moveable(const Moveable &other)
    : angled_position(other.angled_position),
      mask(other.mask.get_radio(), angled_position.get_ref_origin()) {}

Point Moveable::collision_mask_bound(const Point &next_position) {
  double angle = angled_position.get_origin().angle_to(next_position);

  double front_x = next_position.getX() + cos(angle) * mask.get_radio();
  double front_y = next_position.getY() + sin(angle) * mask.get_radio();

  return Point(front_x, front_y);
}

bool Moveable::occupies(Point where) { return mask.occupies(where); }
/*
bool Moveable::is_map_free_in_next_position(Point next_position) {
  return map.is_free(next_position, *this);
}

bool Moveable::is_map_free_in_collision_mask_bounds(Point next_position,
                                                    double angle) {
  double front_x = next_position.getX() + cos(angle) * mask.get_radio();
  double front_y = next_position.getY() + sin(angle) * mask.get_radio();

  return map.is_free(Point(front_x, front_y), *this);
}

void Moveable::move_from_current_position_if_can(double direction_angle) {
  double movement_angle = angled_position.get_angle() + direction_angle;

  double next_x =
      angled_position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y =
      angled_position.get_origin().getY() + sin(movement_angle) * pace;

  Point next(next_x, next_y);

  if (is_map_free_in_next_position(next) &&
      is_map_free_in_collision_mask_bounds(next, movement_angle)) {
    angled_position = Ray(next_x, next_y, angled_position.get_angle());
  }
}

// TODO return bool if successful, or point of result, to confirm to client his
// new position or decline it
void Moveable::move_up() { move_from_current_position_if_can(0); }

void Moveable::move_down() { move_from_current_position_if_can(M_PI); }

void Moveable::move_right() { move_from_current_position_if_can(3 * M_PI / 2); }

void Moveable::move_left() { move_from_current_position_if_can(M_PI / 2); }

void Moveable::move_up_right() {
  move_from_current_position_if_can(7 * M_PI / 4);
}

void Moveable::move_up_left() { move_from_current_position_if_can(M_PI / 4); }

void Moveable::move_down_right() {
  move_from_current_position_if_can(5 * M_PI / 4);
}

void Moveable::move_down_left() {
  move_from_current_position_if_can(3 * M_PI / 4);
}*/

bool Moveable::operator!=(const Moveable &other) const {
  return (this != &other);
}

void Moveable::set_position(const Point &new_origin) {
  angled_position = Ray(new_origin, angled_position.get_angle());
}
