#include "angle.h"

#include <cmath>

Angle::Angle(double angle) : angle(normalize(angle)) {}

Angle::~Angle() {}

double Angle::normalize(double angle) {
  if (angle >= 2 * M_PI) {
    do {
      angle -= 2 * M_PI;
    } while (angle > 2 * M_PI);
  }
  if (angle < 0) {
    do {
      angle += 2 * M_PI;
    } while (angle < 0);
  }
  return angle;
}

double Angle::to_double() const { return angle; }

Angle Angle::operator+(Angle& other) {
  return Angle(this->angle + other.angle);
}
Angle Angle::operator-(Angle& other) {
  return Angle(this->angle - other.angle);
}
void Angle::operator+=(Angle& other) {
  this->angle = normalize(this->angle + other.angle);
}
void Angle::operator-=(Angle& other) {
  this->angle = normalize(this->angle - other.angle);
}

Angle Angle::operator+(double angle) { return Angle(this->angle + angle); }

Angle Angle::operator-(double angle) { return Angle(this->angle - angle); }

void Angle::operator+=(double angle) {
  this->angle = normalize(this->angle + angle);
}

void Angle::operator-=(double angle) {
  this->angle = normalize(this->angle - angle);
}
