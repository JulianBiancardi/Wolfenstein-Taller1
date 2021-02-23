#include "rocket.h"

#include "../../../../../common/src/main/ids/map_ids.h"

// TODO Add res_id
Rocket::Rocket(const Ray& position, unsigned int id, unsigned int owner_id)
    : IdentifiableObject(position, ROCKET, id), owner_id(owner_id) {}

void Rocket::move() {
  const Point& current_position = position.get_origin();
  double angle = position.get_angle();

  double next_x = current_position.getX() + cos(angle) * CL::rocket_speed;
  double next_y = current_position.getY() - sin(angle) * CL::rocket_speed;

  position = Ray(next_x, next_y, angle);
}

unsigned int Rocket::get_owner_id() { return owner_id; }

Image* Rocket::get_image(ResourceManager& resource_manager) {
  return resource_manager.get_image(ROCKET);
}

SDL_Rect* Rocket::get_slice(void* extra) {
  double angle_of_perception =
      Angle::normalize(*(double*) extra - position.get_angle() + M_PI / 8);

  slice.x = ((int) ((angle_of_perception / (M_PI / 4)) + 4) % 8) * 64;
  slice.w = 64;
  slice.h = 64;

  return &slice;
}
