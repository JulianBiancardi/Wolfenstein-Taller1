#ifndef RAY_CASTING_H
#define RAY_CASTING_H

#include "../../../../common/src/main/utils/base_map.h"
#include "../../../../common/src/main/utils/ray.h"
#include "collision.h"

class RayCasting {
 private:
  Collision static first_quad(BaseMap& map, Ray& ray);
  Collision static second_quad(BaseMap& map, Ray& ray);
  Collision static third_quad(BaseMap& map, Ray& ray);
  Collision static forth_quad(BaseMap& map, Ray& ray);
  Collision static horizontal_axis(BaseMap& map, Ray& ray);
  Collision static vertical_axis(BaseMap& map, Ray& ray);

 public:
  RayCasting() = delete;
  ~RayCasting() = delete;

  /* Receives a Map, a Ray the collision which occurs upon casting the ray onto
   * the map.
   * Preconditions:
   *  -The ray must be able to hit a wall in its direction.
   *  -The ray's angle must be normalized to [0, 2*PI).
   */
  Collision static get_collision(BaseMap& m, Ray& ray);

  double static get_scaling_factor(Ray& ray, Ray& player_direction,
                                   Collision& intersection_point);
};

#endif
