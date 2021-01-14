#ifndef WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
#define WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_

#include <cmath>
#include <cstddef>

#include "box_mask.h"
#include "mask.h"

class Map;

class Circle_mask : public Mask {
 private:
  double radio;

 public:
  Circle_mask(double radio, const Point &center)
      : radio(radio), Mask(center) {};
  ~Circle_mask() {};

  virtual bool occupies(Point where);
  double get_radio() const { return radio; };
};

#endif  // WOLFENSTEIN_TALLER1_SRC_MAIN_SERVER_GAME_COLLISIONS_CIRCLE_MASK_H_
