#include "SDL2/SDL.h"
#include "src/main/window.h"

void static handle_key_press(SDL_Keycode& key);

int main(int main, char** argv) {
  Window window("Movement Test", 320, 200);
  window.fill(255, 255, 255, 255);
  window.update();

  SDL_Event event;
  bool run = true;
  while (run) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          run = false;
          break;
        case SDL_KEYDOWN:
          printf("Key press\n");
          handle_key_press(event.key.keysym.sym);
          break;
        case SDL_KEYUP:
          printf("Key release\n");
          break;
        case SDL_MOUSEBUTTONDOWN:
          printf("Mouse clicked\n");
          break;
        case SDL_MOUSEBUTTONUP:
          printf("Mouse unclicked\n");
          break;
        default:
          break;
      }
    }
  }
}

void static handle_key_press(SDL_Keycode& key) {
  switch (key) {
    case SDLK_w:
      printf("W\n");
      break;
    case SDLK_s:
      printf("S\n");
      break;
    case SDLK_a:
      printf("A\n");
      break;
    case SDLK_d:
      printf("D\n");
      break;
    default:
      break;
  }
}