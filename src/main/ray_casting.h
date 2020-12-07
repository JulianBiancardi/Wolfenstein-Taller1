#ifndef RAY_CASTING_H
#define RAY_CASTING_H

#include "map.h"
#include "utils/point.h"
#include "utils/ray.h"

class RayCasting {
 private:
  Point static first_quad(Map& map, Ray& ray, bool& y_intersection);
  Point static second_quad(Map& map, Ray& ray, bool& y_intersection);
  Point static third_quad(Map& map, Ray& ray, bool& y_intersection);
  Point static forth_quad(Map& map, Ray& ray, bool& y_intersection);
  Point static horizontal_axis(Map& map, Ray& ray);
  Point static vertical_axis(Map& map, Ray& ray);

 public:
  RayCasting() = delete;
  ~RayCasting() = delete;

  /* Receives a Map, a Ray and a boolean, and returns a point of collision which
   * occurs upon casting the ray onto the map. Sets the passed boolean to True
   * if the collision occurs with a y=K line, False if the collision occurs
   * with a x=K line. Precondition: The ray must be able to hit a wall in
   * its direction.
   */
  Point static get_intersection(Map& m, Ray& ray, bool& vert_intersection);

  double static get_scaling_factor(Ray& ray, Ray& player_direction,
                                   Point& intersection_point);
};

#endif
