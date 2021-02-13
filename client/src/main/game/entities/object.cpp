#include "object.h"

#include "../../../../../common/src/main/ids/map_ids.h"

Object::Object(const Ray& position) : position(position) {}

Object::~Object() {}

Point Object::get_position() const { return position.get_origin(); }

double Object::get_angle() const { return position.get_angle(); }

Image* Object::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(
      1);  // TODO Let everyone decide for themselves
}