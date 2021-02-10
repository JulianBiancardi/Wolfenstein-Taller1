#ifndef HUD_H
#define HUD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../player.h"

class Hud {
 private:
  SDL_Renderer *renderer;

 public:
  Hud(SDL_Renderer *renderer);
  ~Hud();

  void update(const Player &player) const;
};

#endif  // HUD_H