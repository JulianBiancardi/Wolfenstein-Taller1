#include "moveable.h"
#include "../../map.h"
#include <cmath>

Moveable::Moveable(Point origin, double angle, Map &game_map, int pace) :
    angled_position(origin, angle),
    map(game_map),
    pace(pace),
    mask(5) {}

void Moveable::move_from_current_position_if_can(double direction_angle) {
  double movement_angle = angled_position.get_angle() + direction_angle;
  //if (movement_angle >= 2 * M_PI) movement_angle -= 2 * M_PI;
  double next_x = angled_position.get_origin().getX() +
      cos(movement_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(movement_angle) * pace;
  if (map.is_free(next_x, next_y, *this, movement_angle))
    angled_position.set_origin(next_x, next_y);
}

bool Moveable::collides(size_t x, size_t y, Player &what) {
  return mask.collides(x, y, what.get_mask(), what.get_position());
}

bool Moveable::collides(size_t x, size_t y, Object &what) {
  return mask.collides(x, y, what.get_mask(), what.get_position());
}

bool Moveable::collides_wall(size_t x, size_t y, double movement_angle) {
  return mask.collides_wall(x, y, map, movement_angle);
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
