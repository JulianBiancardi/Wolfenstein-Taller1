#include <SDL2/SDL.h>

#include "sdl_window.h"

const int WIDTH = 320;
const int HEIGHT = 320;

int main(int args, char** argv) {
  SDLWindow main_window = SDLWindow("Editor", WIDTH, HEIGHT);

  SDL_Event windowEvent;

  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) {
        break;
      }
    }
  }

  return 0;
}