#ifndef MATCH_MAKER_CASTER_H
#define MATCH_MAKER_CASTER_H

#include "../sdl/window.h"
#include "caster.h"

class MatchMakerCaster : public Caster {
 private:
  Window& window;

 public:
  explicit MatchMakerCaster(Window& window);
  ~MatchMakerCaster();

  void operator()() override;
};

#endif
