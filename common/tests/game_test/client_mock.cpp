#include "client_mock.h"
#include <cmath>

// TODO try to use server and client code
Point next_position(double direction_angle, Ray angled_position) {
  double movement_angle = angled_position.get_angle() + direction_angle;

  double next_x = angled_position.get_origin().getX() +
      cos(movement_angle) * 1;
  double next_y = angled_position.get_origin().getY() +
      sin(movement_angle) * 1;

  return Point(next_x, next_y);
}

Point next_position_up(Ray angled_position) {
  return next_position(0, angled_position);
}

Point next_position_down(Ray angled_position) {
  return next_position(M_PI, angled_position);
}

Point next_position_right(Ray angled_position) {
  return next_position(3 * M_PI / 2, angled_position);
}

Point next_position_left(Ray angled_position) {
  return next_position(M_PI / 2, angled_position);
}

Point next_position_up_right(Ray angled_position) {
  return next_position(7 * M_PI / 4, angled_position);
}

Point next_position_up_left(Ray angled_position) {
  return next_position(M_PI / 4, angled_position);
}

Point next_position_down_right(Ray angled_position) {
  return next_position(5 * M_PI / 4, angled_position);
}

Point next_position_down_left(Ray angled_position) {
  return next_position(3 * M_PI / 4, angled_position);
}

// TODO Should not be here
void put_data(Matrix<int> &map_data) {
  for (int j = 0; j < 64; j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      map_data(i, j) = WALL;  // TOP
      map_data(j, i) = WALL;  // LEFT
      map_data(i, map_data.get_rows() - 1 - j) = WALL;  // BOT
      map_data(map_data.get_columns() - 1 - j, i) = WALL;  // RIGHT
    }
  }
}
