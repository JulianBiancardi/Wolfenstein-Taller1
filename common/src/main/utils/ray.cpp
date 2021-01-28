#include "ray.h"

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::Ray(double x, double y, double angle)
    : origin(Point(x, y)), angle(angle) {}

Ray::~Ray() {}

Point Ray::get_origin() const { return origin; }

const Point &Ray::get_ref_origin() const { return origin; }

double Ray::get_angle() const { return angle.to_double(); }
