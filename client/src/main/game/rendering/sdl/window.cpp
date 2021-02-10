#include "window.h"

#include "sdl_error.h"

#define ERROR -1
#define NO_ERROR 0

Window::Window(const std::string& title, int width, int height)
    : width(width), height(height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw SDLError("SDLError: failed to initialize - %s\n", SDL_GetError());
  }

  if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED,
                                  &this->window, &this->renderer) < 0) {
    throw SDLError("SDLError: failed to create window and renderer - %s\n",
                   SDL_GetError());
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
    throw SDLError("SDLError: failed to clear renderer - %s\n", SDL_GetError());
  }
  return NO_ERROR;
}

int Window::set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (SDL_SetRenderDrawColor(renderer, r, g, b, a) != NO_ERROR) {
    throw SDLError("SDLError: failed to set drawing color - %s\n",
                   SDL_GetError());
  }
  return NO_ERROR;
}

int Window::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  set_draw_color(r, g, b, a);
  clear();
  return NO_ERROR;
}

int Window::draw_line(int x1, int y1, int x2, int y2) {
  if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) != NO_ERROR) {
    throw SDLError("SDLError: failed to draw line - %s\n", SDL_GetError());
  }
  return NO_ERROR;
}

void Window::update() { SDL_RenderPresent(renderer); }

SDL_Renderer* Window::get_renderer() { return renderer; }