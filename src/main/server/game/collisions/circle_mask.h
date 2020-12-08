#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_

#include "mask.h"
#include "box_mask.h"
#include <cstddef>
#include <cmath>

class Map;

class Circle_mask : public Mask {
 private:
  double radio;

 public:
  Circle_mask(double radio);
  ~Circle_mask() {};
  virtual bool collides(size_t where_x,
                        size_t where_y,
                        Circle_mask &other,
                        Point other_position);
  bool collides(size_t where_x,
                size_t where_y,
                Mask *other,
                Point other_position);
  bool collides_wall(size_t where_x,
                     size_t where_y,
                     Map &map,
                     double movement_angle);
  double get_radio() { return radio; };
};

#endif //WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
