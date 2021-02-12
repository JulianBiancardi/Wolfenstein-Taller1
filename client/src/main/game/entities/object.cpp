#include "object.h"

#include "../../../../../common/src/main/ids/map_ids.h"

Object::Object(unsigned char res_id, Ray position)
    : res_id(res_id), position(position) {}

Object::~Object() {}

unsigned char Object::get_res_id() { return res_id; }

Point Object::get_position() const { return position.get_origin(); }

double Object::get_angle() const { return position.get_angle(); }

unsigned char Object::get_type() const {
  if (res_id == NULL_TYPE) {
    return NULL_TYPE;
  } else if (res_id < SPAWN_POINT) {
    return WALLS_TYPE;
  } else if (res_id < KNIFE) {
    return PLAYERS_TYPE;
  } else if (res_id < FOOD) {
    return GUNS_TYPE;
  } else if (res_id < PILLAR) {
    return ITEMS_TYPE;
  } else if (res_id < WATER) {
    return SOLID_OBJECTS_TYPE;
  } else if (res_id < DOOR) {
    return NON_SOLID_OBJECTS_TYPE;
  } else {
    NULL_TYPE;
  }
}