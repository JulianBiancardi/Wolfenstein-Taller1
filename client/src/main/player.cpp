#include "player.h"
#include <cmath>

Player::Player(Point origin, double angle)
    : angled_position(origin, angle) {
  pace = 1; // TODO Use config file
}

Player::Player(double x, double y, double angle)
    : angled_position(x, y, angle) {
  pace = 1; // TODO Use config file
}

Point Player::next_position(double direction_angle) {
  double movement_angle = angled_position.get_angle() + direction_angle;

  double next_x = angled_position.get_origin().getX() +
      cos(movement_angle) * pace;
  double next_y = angled_position.get_origin().getY() +
      sin(movement_angle) * pace;

  return Point(next_x, next_y);
}

Point Player::next_position_up() { return next_position(0); }

Point Player::next_position_down() { return next_position(M_PI); }

Point Player::next_position_right() {
  return next_position(3 * M_PI / 2);
}

Point Player::next_position_left() {
  return next_position(M_PI / 2);
}

Point Player::next_position_up_right() {
  return next_position(7 * M_PI / 4);
}

Point Player::next_position_up_left() {
  return next_position(M_PI / 4);
}

Point Player::next_position_down_right() {
  return next_position(5 * M_PI / 4);
}

Point Player::next_position_down_left() {
  return next_position(3 * M_PI / 4);
}

void Player::set_position(const Point &new_origin) {
  angled_position.set_origin(new_origin);
}
