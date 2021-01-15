#include "hit.h"

Hit::Hit(int object_id, int damage) : object_id(object_id), damage(damage) {}

Hit::~Hit() {}

Hit::Hit(Hit&& other) {
  this->object_id = other.object_id;
  this->damage = other.damage;

  other.object_id = -1;
  other.damage = 0;
}

Hit& Hit::operator=(Hit&& other) {
  if (this == &other) {
    return *this;
  }
  object_id = other.object_id;
  damage = other.damage;

  other.object_id = -1;
  other.damage = 0;

  return *this;
}

int Hit::get_damage() { return damage; }

int Hit::get_object_id() { return object_id; }
