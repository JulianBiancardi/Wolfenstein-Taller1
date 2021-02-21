#include "switch_mask.h"

// Mask starts active
SwitchMask::SwitchMask(Mask* mask)
    : Mask(mask->get_center()), mask(mask), active(true) {}

SwitchMask::~SwitchMask() { delete mask; }

void SwitchMask::switch_mask() { active = !active; }

bool SwitchMask::is_active() const { return active; }

bool SwitchMask::occupies(const Point& where) const {
  if (active) {
    return mask->occupies(where);
  } else {
    return false;
  }
}

Mask* SwitchMask::get_copy(const Point& center) {
  return new SwitchMask(mask->get_copy(center));
}

Mask* SwitchMask::get_mask() const { return mask; }
