#include "angle.h"

#include <cmath>

Angle::Angle(double value) {
  if (value >= 2 * M_PI) {
    do {
      value -= 2 * M_PI;
    } while (value > 2 * M_PI);
  } else if (value < 0) {
    do {
      value += 2 * M_PI;
    } while (value < 0);
  }
  angle = value;
}

Angle::~Angle() {}

double Angle::to_double() { return angle; }
