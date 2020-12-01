#include "ray.h"

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::Ray(int x, int y, double angle) : origin(Point(x, y)), angle(angle) {}

Ray::~Ray() {}

Point Ray::get_origin() { return origin; }

// TODO Delete this method, make Ray immutable
void Ray::set_origin(int x, int y) { origin = Point(x, y); }

double Ray::get_angle() { return angle; }

// TODO Delete this method, make Ray immutable
void Ray::set_angle(double angle) { this->angle = angle; }