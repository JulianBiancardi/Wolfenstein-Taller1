#include "ray.h"

Ray::Ray(Point origin, double angle) : origin(origin), angle(angle) {}

Ray::Ray(double x, double y, double angle)
    : origin(Point(x, y)), angle(angle) {}

Ray::~Ray() {}

Point Ray::get_origin() { return origin; }

const Point &Ray::get_ref_origin() { return origin; }

// TODO Delete this method, make Ray immutable
void Ray::set_origin(double x, double y) { origin = Point(x, y); }

double Ray::get_angle() { return angle; }

// TODO Delete this method, make Ray immutable
void Ray::set_angle(double angle) { this->angle = angle; }