#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#include <string>

class Window {
 private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  int width = 320;
  int height = 320;

 public:
  Window(const std::string& title, int width, int height);

  Window(const Window&) = delete;              // No copy constructor
  Window& operator=(const Window&) = delete;   // No copy constructor
  Window(Window&& other) = delete;             // No move constructor
  Window& operator=(Window&& other) = delete;  // No move constructor

  ~Window();
};

#endif
