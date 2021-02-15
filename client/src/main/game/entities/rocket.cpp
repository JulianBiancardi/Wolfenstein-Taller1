#include "rocket.h"

#include "../../../../../common/src/main/ids/map_ids.h"

// TODO Add res_id
Rocket::Rocket(Ray& position, unsigned int id, unsigned int owner_id)
    : IdentifiableObject(position, 1, id), owner_id(owner_id) {}

void Rocket::move() {
  const Point& current_position = position.get_origin();
  double angle = position.get_angle();

  double next_x = current_position.getX() + cos(angle) * CL::rocket_speed;
  double next_y = current_position.getY() - sin(angle) * CL::rocket_speed;

  position = Ray(next_x, next_y, angle);
}

unsigned int Rocket::get_owner_id() { return owner_id; }

Image* Rocket::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(1);  // TODO Put correct image
}
