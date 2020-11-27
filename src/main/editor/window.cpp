#include "window.h"

#include "constants.h"

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

int Window::clear() {
  if (SDL_RenderClear(renderer) != NO_ERROR) {
    return -1;  // TODO Throw Exception
  }
  return NO_ERROR;
}

int Window::set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (SDL_SetRenderDrawColor(renderer, r, g, b, a) != NO_ERROR) {
    return -1;  // TODO Throw Exception
  }
  return NO_ERROR;
}

int Window::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  set_draw_color(r, g, b, a);
  clear();
  return NO_ERROR;
}
