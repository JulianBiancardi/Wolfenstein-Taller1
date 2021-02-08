#include "hit.h"

Hit::Hit(int object_id, int damage, int bullets_used)
    : object_id(object_id), damage(damage), bullets_used(bullets_used) {}

Hit::~Hit() {}

Hit::Hit(Hit&& other) {
  this->object_id = other.object_id;
  this->damage = other.damage;
  this->bullets_used = other.bullets_used;

  other.object_id = -1;
  other.damage = 0;
  other.bullets_used = 0;
}

Hit& Hit::operator=(Hit&& other) {
  if (this == &other) {
    return *this;
  }
  object_id = other.object_id;
  damage = other.damage;
  bullets_used = other.bullets_used;

  other.object_id = -1;
  other.damage = 0;
  other.bullets_used = 0;

  return *this;
}

int Hit::get_damage() { return damage; }

int Hit::get_object_id() { return object_id; }

int Hit::get_bullets_used() { return bullets_used; }
