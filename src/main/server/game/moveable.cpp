#include "moveable.h"
#include "../../map.h"
#include <cmath>

Moveable::Moveable(Point origin, double angle, Map &game_map, int pace) :
    angled_position(origin, angle),
    map(game_map),
    pace(pace),
    mask(5, angled_position.get_origin()) {}

bool Moveable::occupies(Point where) {
  return mask.occupies(where);
}

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

  double next_x = angled_position.get_origin().getX() +
      cos(movement_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(movement_angle) * pace;

  Point next(next_x, next_y);

  if (is_map_free_in_next_position(next)
      && is_map_free_in_collision_mask_bounds(next, movement_angle)) {
    angled_position.set_origin(next_x, next_y);
    mask.update_center(next);
  }
}

void Moveable::move_up() {
  move_from_current_position_if_can(0);
}

void Moveable::move_down() {
  move_from_current_position_if_can(M_PI);
}

void Moveable::move_right() {
  move_from_current_position_if_can(3 * M_PI / 2);
}

void Moveable::move_left() {
  move_from_current_position_if_can(M_PI / 2);
}

void Moveable::move_up_right() {
  move_from_current_position_if_can(7 * M_PI / 4);
}

void Moveable::move_up_left() {
  move_from_current_position_if_can(M_PI / 4);
}

void Moveable::move_down_right() {
  move_from_current_position_if_can(5 * M_PI / 4);
}

void Moveable::move_down_left() {
  move_from_current_position_if_can(3 * M_PI / 4);
}

bool Moveable::operator!=(const Moveable &other) const {
  return (this != &other);
}
