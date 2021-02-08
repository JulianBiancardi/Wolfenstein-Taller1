#ifndef SWITCH_MASK_H
#define SWITCH_MASK_H

#include "../../../../../common/src/main/utils/point.h"
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

#endif