#include "collision.h"

Collision::Collision(int collided_obj_id, Point point, double distance_from_src,
                     bool x_collision)
    : collided_obj_id(collided_obj_id),
      collision_point(point),
      distance_from_src(distance_from_src),
      x_collision(x_collision) {}

Collision::~Collision() {}

int Collision::get_collided_obj_id() { return collided_obj_id; }

Point Collision::get_collision_point() { return collision_point; }

double Collision::get_distance_from_src() { return distance_from_src; }

void Collision::add_distance(double dst) { distance_from_src += dst; }

bool Collision::is_x_collision() { return x_collision; }