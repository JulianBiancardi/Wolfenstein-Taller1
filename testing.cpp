#include <SDL2/SDL.h>

#include <iostream>

const int WIDTH = 320;
const int HEIGHT = 320;

int main(int argc, char** argv) {
  SDL_Surface* hello;
  SDL_Surface* screen;
  SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                                        SDL_WINDOW_ALLOW_HIGHDPI);
  if (window == NULL) {
    std::cout << "ERROR";
  }
  SDL_Event windowEvent;

  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) {
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}