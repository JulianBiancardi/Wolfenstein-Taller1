#include "horizontal_door2.h"

HorizontalDoor2::HorizontalDoor2(size_t x, size_t y, unsigned int resource_id)
    : BaseDoor(x, y, resource_id) {}

HorizontalDoor2::~HorizontalDoor2() {}

bool HorizontalDoor2::update_collision(Collision& collision, double angle) {
  bool hit_door = false;
  double tg = fabs(tan(angle));
  double x = collision.get_collision_point().getX();
  double y = collision.get_collision_point().getY();
  if (angle > 0 && angle < M_PI_2) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * (1 - dx);
    if (delta_y < 0.5) {  // Hitting side
      new_collision_point = Point(x + (1 - dx), y - delta_y);
      collision.collided_obj_id = 72;
      collision.x_collision = true;
    } else {
      new_collision_point = Point(x + 0.5 / tg, y - 0.5);
      hit_door = true;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
  } else if (angle == M_PI_2) {
    Point new_collision_point(x, y - 0.5);
    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    hit_door = true;
  } else if (angle > M_PI_2 && angle < M_PI) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * dx;
    if (delta_y < 0.5) {  // Hitting side
      new_collision_point = Point(x - dx, y - delta_y);
      collision.collided_obj_id = 72;  // FIXME Too hardcoded
      collision.x_collision = true;
    } else {
      new_collision_point = Point(x - 0.5 / tg, y - 0.5);
      hit_door = true;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
  } else if (angle > M_PI && angle < 3 * M_PI_2) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * dx;
    if (delta_y < 0.5) {  // HItting side
      new_collision_point = Point(x - dx, y + delta_y);
      collision.collided_obj_id = 72;
      collision.x_collision = true;
    } else {
      new_collision_point = Point(x - 0.5 / tg, y + 0.5);
      hit_door = true;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
  } else if (angle == 3 * M_PI_2) {
    Point new_collision_point(x, y + 0.5);
    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
    hit_door = true;
  } else if (angle > 3 * M_PI_2 && angle <= 2 * M_PI) {
    Point new_collision_point(x, y);

    double dx = std::fmod(x, 1);
    double delta_y = tg * (1 - dx);
    if (delta_y < 0.5) {  // Hitting side
      new_collision_point = Point(x + (1 - dx), y + delta_y);
      collision.collided_obj_id = 72;
      collision.x_collision = true;
    } else {
      new_collision_point = Point(x + 0.5 / tg, y + 0.5);
      hit_door = true;
    }

    double extra_dist =
        Point::distance(new_collision_point, collision.get_collision_point());
    collision.collision_point = new_collision_point;
    collision.distance_from_src += extra_dist;
  }
  return hit_door;
}
