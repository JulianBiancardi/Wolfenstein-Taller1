#ifndef PASSAGE_H
#define PASSAGE_H

#include "door.h"

class Passage : public Door {
 public:
  Passage(const Point& center, unsigned int id);

  /* Returns if the door state changed */
  bool open(Player& who) override;

  /* Returns if the door should be automatically closed */
  bool should_close_automatically() const override;
};

#endif
