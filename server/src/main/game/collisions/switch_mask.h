#ifndef SWITCH_MASK_H
#define SWITCH_MASK_H

#include "../../../../../common/src/main/utils/point.h"
#include "mask.h"

class SwitchMask : public Mask {
 private:
  bool active;
  Mask* mask;

 public:
  explicit SwitchMask(Mask* mask);
  ~SwitchMask();

  /* Changes the state of the mask.
   * If the mask is active, it occupies its surface. If it is not, it is turned off.
   */
  void switch_mask();

  /* Returns the state of the mask */
  bool is_active() const;

  /* Returns if the mask occupies the point sent or not */
  bool occupies(const Point& where) const override;
};

#endif