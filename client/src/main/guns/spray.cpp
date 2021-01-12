#include "spray.h"

Spray::Spray(double spray_angle, double std_dev)
    : spray_angle(spray_angle / 2),
      generator(),
      normal_distribution(0, std_dev) {}

Spray::~Spray() {}

double Spray::operator()() {
  double angle;
  do {
    angle = normal_distribution(generator);
  } while (spray_angle < fabs(angle));  // Truncate to certain angle
  return angle;
}