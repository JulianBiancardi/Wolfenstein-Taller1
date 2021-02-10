#ifndef SPRAY_H
#define SPRAY_H

#include <random>

class Spray {
 private:
  double spray_angle;
  std::default_random_engine generator;
  std::normal_distribution<double> normal_distribution;

 public:
  Spray(double spray_angle, double std_dev);
  ~Spray();

  double operator()();
};

#endif
