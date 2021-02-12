#ifndef ROCKET_H
#define ROCKET_H

<<<<<<< HEAD:client/src/main/game/entities/rocket.h
#include "identifiable_object.h"
=======
#include "../entities/object.h"
>>>>>>> c45cc697f4d5663c99645f75f2a74d9b0743ad6b:client/src/main/game/guns/rocket.h

class Rocket : public IdentifiableObject {
 public:
  Rocket(const Point& position, double angle, unsigned int id);

  /* Moves the rocket */
  void move();
};

#endif
