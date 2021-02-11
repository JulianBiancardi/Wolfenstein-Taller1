#include "hit.h"

Hit::Hit(unsigned char gun_id, int object_id, int damage, bool shot)
    : gun_id(gun_id), object_id(object_id), damage(damage), shot(shot) {}

Hit::~Hit() {}

Hit::Hit(Hit&& other) {
  this->gun_id = other.gun_id;
  this->object_id = other.object_id;
  this->damage = other.damage;
  this->shot = other.shot;

  other.gun_id = 0;
  other.object_id = -1;
  other.damage = 0;
  other.shot = false;
  ;
}

Hit& Hit::operator=(Hit&& other) {
  if (this == &other) {
    return *this;
  }

  gun_id = other.gun_id;
  object_id = other.object_id;
  damage = other.damage;
  shot = other.shot;

  other.gun_id = 0;
  other.object_id = -1;
  other.damage = 0;
  other.shot = false;

  return *this;
}

unsigned char Hit::get_gun_id() { return gun_id; }

int Hit::get_damage() { return damage; }

int Hit::get_object_id() { return object_id; }

bool Hit::is_shot() { return shot; }
