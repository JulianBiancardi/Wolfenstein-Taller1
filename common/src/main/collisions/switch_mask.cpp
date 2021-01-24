#include "switch_mask.h"

// Mask starts active
SwitchMask::SwitchMask(Mask* mask)
    : Mask(mask->get_center()), mask(mask), active(true) {}

void SwitchMask::switch_mask() { active = !active; }

bool SwitchMask::is_active() { return active; }

bool SwitchMask::occupies(const Point& where) {
  if (active)
    return mask->occupies(where);
  else
    return false;
}

SwitchMask::~SwitchMask() { delete mask; }
