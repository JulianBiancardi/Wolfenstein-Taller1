#ifndef ANGLE_H
#define ANGLE_H

/* Class representing an angle between 0 and 2PI */
class Angle {
 private:
  double angle;

 public:
  Angle(double angle);
  ~Angle();

  /* Returns the value of the angle between 0 and 2PI */
  static double normalize(double angle);

  /* Returns the value of the angle as a double */
  double to_double() const;

  Angle operator+(Angle& other);
  Angle operator-(Angle& other);
  void operator+=(Angle& other);
  void operator-=(Angle& other);

  Angle operator+(double angle);
  Angle operator-(double angle);
  void operator+=(double angle);
  void operator-=(double angle);
};

#endif
