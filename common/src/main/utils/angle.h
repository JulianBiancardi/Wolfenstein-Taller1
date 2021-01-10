#ifndef ANGLE_H
#define ANGLE_H

/* Class representing an angle between 0 and 2PI */
class Angle {
 private:
  double angle;

 public:
  Angle(double angle);
  ~Angle();

  /* Returns the value of the angle */
  double to_double();
};

#endif
