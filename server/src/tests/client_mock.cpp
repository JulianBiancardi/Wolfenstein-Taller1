#include "client_mock.h"
#include <cmath>

// TODO try to use server and client code
Point next_position(double direction_angle,
                    const Point& position,
                    const Angle& angle) {
  double movement_angle = angle.to_double() + direction_angle;

  double next_x = position.getX() + cos(movement_angle) * 1;
  double next_y = position.getY() - sin(movement_angle) * 1;

  return Point(next_x, next_y);
}

Point next_position_up(const Point& position, const Angle& angle) {
  return next_position(0, position, angle);
}

Point next_position_down(const Point& position, const Angle& angle) {
  return next_position(M_PI, position, angle);
}

Point next_position_right(const Point& position, const Angle& angle) {
  return next_position(3 * M_PI / 2, position, angle);
}

Point next_position_left(const Point& position, const Angle& angle) {
  return next_position(M_PI / 2, position, angle);
}

Point next_position_up_right(const Point& position, const Angle& angle) {
  return next_position(7 * M_PI / 4, position, angle);
}

Point next_position_up_left(const Point& position, const Angle& angle) {
  return next_position(M_PI / 4, position, angle);
}

Point next_position_down_right(const Point& position, const Angle& angle) {
  return next_position(5 * M_PI / 4, position, angle);
}

Point next_position_down_left(const Point& position, const Angle& angle) {
  return next_position(3 * M_PI / 4, position, angle);
}

// TODO Should not be here
void put_data(Matrix<int>& map_data) {
  for (int j = 0; j < 64; j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      map_data(i, j) = WALL;  // TOP
      map_data(j, i) = WALL;  // LEFT
      map_data(i, map_data.get_rows() - 1 - j) = WALL;  // BOT
      map_data(map_data.get_columns() - 1 - j, i) = WALL;  // RIGHT
    }
  }
}

// TODO Should not be here
void put_data_on_borders(Matrix<int>& map_data) {
  for (int j = 0; j < map_data.get_rows(); j++) {
    for (int i = 0; i < map_data.get_columns(); i++) {
      if ((j == map_data.get_rows() - 1) || (j == 0) ||
          (i == map_data.get_columns() - 1) || (i == 0)) {
        map_data(j, i) = WALL;
      }
    }
  }
}

bool double_compare(double x, double y) {
  return fabs(x - y) < EPSILON;
}
