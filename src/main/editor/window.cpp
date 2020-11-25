#include "window.h"

Window::Window(const std::string& title, int width, int height)
    : width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw -1;  // TODO Add SDLException
  }

  // TODO Consider splitting Window and Renderer into their own classes.
  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                  &this->window, &this->renderer) < 0) {
    throw -1;  // TODO Add SDLException
  }
  SDL_SetWindowTitle(this->window, title.c_str());
}

Window::~Window() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
}