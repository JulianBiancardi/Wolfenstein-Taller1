#include "player.h"

#include <cmath>

#include "casting/ray_casting.h"

Player::Player(Point origin, double angle) : position(origin, angle) {
  pace = 1;  // TODO Use config file
}

Player::Player(double x, double y, double angle) : position(x, y, angle) {
  pace = 1;  // TODO Use config file
}

Point Player::next_position(double direction_angle) {
  double movement_angle = position.get_angle() + direction_angle;

  double next_x = position.get_origin().getX() + cos(movement_angle) * pace;
  double next_y = position.get_origin().getY() + sin(movement_angle) * pace;

  return Point(next_x, next_y);
}

Point Player::next_position_up() { return next_position(0); }

Point Player::next_position_down() { return next_position(M_PI); }

Point Player::next_position_right() { return next_position(3 * M_PI / 2); }

Point Player::next_position_left() { return next_position(M_PI / 2); }

Point Player::next_position_up_right() { return next_position(7 * M_PI / 4); }

Point Player::next_position_up_left() { return next_position(M_PI / 4); }

Point Player::next_position_down_right() { return next_position(5 * M_PI / 4); }

Point Player::next_position_down_left() { return next_position(3 * M_PI / 4); }

void Player::set_position(const Point& new_origin) {
  position = Ray(new_origin, position.get_angle());
}

void Player::shoot(Map& map) {
  double angle = position.get_angle();
  Ray bullet = position;  // TODO Make some probabilistic shot
  double wall_distance =
      RayCasting::get_collision(map, bullet).get_distance_from_src();

  std::vector<Object> objects = map.get_objects();
  // TODO Sort objects from closest to farthest, to only hit closest.
  std::vector<Object>::iterator iter;
  for (iter = objects.begin(); iter != objects.end(); iter++) {
    Object& object = *iter;
    // TODO Consider: if (!object.is_solid()) {continue;}
    double object_distance =
        object.get_position().distance_from(position.get_origin());
    // This can be used to limit weapon range
    if (object_distance >= wall_distance) {
      continue;
    }

    // As a decision of implementation design, solid objects have same radius
    // TODO Change number 1 to use ConfigLoader and use the actual size of
    // things.
    double half_angular_diameter = atan(1 / object_distance);
    double object_angle = object.get_position().angle_to(position.get_origin());

    double left_angle = object_angle + half_angular_diameter;
    if (left_angle > 2 * M_PI) {
      left_angle -= 2 * M_PI;
    }

    double right_angle = object_angle - half_angular_diameter;
    if (right_angle < 0) {
      right_angle += 2 * M_PI;
    }

    // Check if bullet angle is between object angular diameter
    double rel_angle =
        std::fmod(std::fmod(left_angle - right_angle, 360) + 360, 360);
    if (rel_angle >= 180) {
      std::swap(left_angle, right_angle);
    }

    bool hit = false;
    double bullet_angle = bullet.get_angle();
    if (right_angle <= left_angle) {
      hit = bullet_angle >= right_angle && bullet_angle <= left_angle;
    } else {
      hit = bullet_angle >= right_angle || bullet_angle <= left_angle;
    }
    // TODO We know we hit the object. Proceed with whatever is necessary.
  }
}

//
void Player::set_health(int health) { this->health = health; }
