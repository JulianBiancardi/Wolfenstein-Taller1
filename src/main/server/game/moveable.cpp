#include "moveable.h"
#include <cmath>

Moveable::Moveable(Point origin, double angle, Map &game_map, int pace) :
    angled_position(origin, angle), map(game_map), pace(pace) {}

Moveable::Moveable(int x, int y, double angle, Map &game_map, int pace) :
    angled_position(x, y, angle), map(game_map), pace(pace) {}

void Moveable::move_from_current_position_if_can(double direction_angle) {
  double next_x = angled_position.get_origin().getX() +
      cos(angled_position.get_angle() + direction_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(angled_position.get_angle() + direction_angle) * pace;
  if (!map.is_wall(next_x, next_y))
    angled_position.set_origin(next_x, next_y);
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
