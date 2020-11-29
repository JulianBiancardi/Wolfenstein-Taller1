#include "ray.h"

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::Ray(int x, int y, double angle) : origin(Point(x, y)), angle(angle) {}

Ray::~Ray() {}

Point Ray::get_origin() { return origin; }

double Ray::get_angle() { return angle; }