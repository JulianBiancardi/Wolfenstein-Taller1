#include "hit.h"

Hit::Hit(int object_id, int damage, bool shot)
    : object_id(object_id), damage(damage), shot(shot) {}

Hit::~Hit() {}

Hit::Hit(Hit&& other) {
  this->object_id = other.object_id;
  this->damage = other.damage;
  this->shot = other.shot;

  other.object_id = -1;
  other.damage = 0;
  other.shot = false;
  ;
}

Hit& Hit::operator=(Hit&& other) {
  if (this == &other) {
    return *this;
  }
  object_id = other.object_id;
  damage = other.damage;
  shot = other.shot;

  other.object_id = -1;
  other.damage = 0;
  other.shot = false;

  return *this;
}

int Hit::get_damage() { return damage; }

int Hit::get_object_id() { return object_id; }

bool Hit::is_shot() { return shot; }
