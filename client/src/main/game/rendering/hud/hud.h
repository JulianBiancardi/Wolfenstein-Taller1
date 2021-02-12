#ifndef HUD_H
#define HUD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../entities/player.h"
#include "../sdl/window.h"

class Hud {
 private:
  SDL_Renderer *renderer;
  TTF_Font *font;

 public:
  Hud(SDL_Renderer *renderer);
  ~Hud();

  void update(const Window &window, const Player &player) const;
};

#endif  // HUD_H