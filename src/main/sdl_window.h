#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL2/SDL.h>

class SDLWindow {
 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int width;
  int height;

 public:
  SDLWindow(int width, int height);
  ~SDLWindow();
};

SDLWindow::SDLWindow(int width, int height) : width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw -1;  // TODO Add SDLException
  }
  // TODO Consider splitting Window and Renderer into their own classes.
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                  &this->window, &this->renderer) < 0) {
    throw -1;  // TODO Add SDLException
  }
}

SDLWindow::~SDLWindow() {
  if (this->renderer) {
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;
  }

  if (this->window) {
    SDL_DestroyWindow(this->window);
    this->window = nullptr;
  }
}

#endif
