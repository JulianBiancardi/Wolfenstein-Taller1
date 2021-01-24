#ifndef WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_
#define WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_

#include "mask.h"

class SwitchMask : public Mask {
 private:
  bool active;
  Mask* mask;

 public:
  SwitchMask(Mask* mask);
  void switch_mask();
  bool is_active();
  bool occupies(const Point& where) override;
  ~SwitchMask();
};

#endif //WOLFENSTEIN_TALLER1_COMMON_SRC_MAIN_COLLISIONS_SWITCH_MASK_H_
