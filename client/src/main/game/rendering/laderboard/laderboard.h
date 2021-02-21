#ifndef LADERBOARD_H
#define LADERBOARD_H

#include <SDL2/SDL.h>

#include <list>

#include "../../entities/player.h"
#include "../sdl/image.h"
#include "../sdl/window.h"

class LaderBoard {
 private:
  SDL_Renderer *renderer;
  const Window &window;
  int scale_x;
  int scale_y;
  Image background;

 public:
  LaderBoard(SDL_Renderer *renderer, const Window &window);
  ~LaderBoard();

  void showTop5();
};

#endif  // LADERBOARD_H