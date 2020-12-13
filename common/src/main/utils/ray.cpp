#include "ray.h"

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::Ray(double x, double y, double angle)
    : origin(Point(x, y)), angle(angle) {}

Ray::~Ray() {}

Point Ray::get_origin() { return origin; }

void Ray::set_origin(const Point &new_origin) { origin = new_origin; }

const Point &Ray::get_ref_origin() { return origin; }

double Ray::get_angle() { return angle; }
