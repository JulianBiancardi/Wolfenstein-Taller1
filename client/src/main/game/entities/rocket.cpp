#include "rocket.h"

#include "../../../../../common/src/main/ids/map_ids.h"

// TODO Add res_id
Rocket::Rocket(Ray& position, unsigned int id)
    : IdentifiableObject(position, id) {}

void Rocket::move() {
  const Point& current_position = position.get_origin();
  double angle = position.get_angle();

  double next_x = current_position.getX() + cos(angle) * CL::rocket_speed;
  double next_y = current_position.getY() - sin(angle) * CL::rocket_speed;

  position = Ray(next_x, next_y, angle);
}

Image* Rocket::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(2);  // TODO Put correct image
}
