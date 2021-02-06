#ifndef WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_
#define WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_

#include "../utils/point.h"
#include "mask.h"

class SwitchMask : public Mask {
 private:
  bool active;
  Mask* mask;

 public:
  SwitchMask(Mask* mask);
  void switch_mask();
  bool is_active();
  bool occupies(const Point& where) const override;
  ~SwitchMask();
};

#endif  // WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_
