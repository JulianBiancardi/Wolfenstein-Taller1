#ifndef ROCKET_H
#define ROCKET_H

#include "../../object.h"

class Rocket : public Object {
 public:
  Rocket(const Point& position, double angle, unsigned int id);

  /* Moves the rocket */
  void move();
};

#endif
