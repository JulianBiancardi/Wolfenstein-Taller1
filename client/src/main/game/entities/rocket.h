#ifndef ROCKET_H
#define ROCKET_H

#include "identifiable_object.h"

class Rocket : public IdentifiableObject {
 public:
  Rocket(Ray& position, unsigned int id);

  /* Moves the rocket */
  void move();

  Image* get_image(ResourceManager& resource_manager) override;
};

#endif
