#ifndef ROCKET_H
#define ROCKET_H

#include "identifiable_object.h"

class Rocket : public IdentifiableObject {
 private:
  unsigned int owner_id;

 public:
  Rocket(const Ray& position, unsigned int id, unsigned int owner_id);

  /* Moves the rocket */
  void move();

  /* Returns owner's id */
  unsigned int get_owner_id();

  virtual Image* get_image(ResourceManager& resource_manager) override;
};

#endif
