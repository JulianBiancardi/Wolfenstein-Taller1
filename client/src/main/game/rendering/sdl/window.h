#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "surface.h"

// TODO https:// github.com/Taller-de-Programacion/valgrind-supp-parser

class Window {
 private:
  SDL_Window* window = nullptr;
  Surface window_icon;
  SDL_Renderer* renderer = nullptr;
  int width = 960;
  int height = 600;

 public:
  Window(const std::string& title, int width, int height, bool fullscreen,
         const std::string& icon_path);

  Window(const Window&) = delete;              // No copy constructor
  Window& operator=(const Window&) = delete;   // No copy constructor
  Window(Window&& other) = delete;             // No move constructor
  Window& operator=(Window&& other) = delete;  // No move constructor

  ~Window();

  /* Clear the current rendering target with the current color */
  int clear();

  /* Fill the background with the RGBA color.
   * Returns 0 on success, throws SDLError otherwise.
   */
  int fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /* Sets the drawing color to the given RGBA color.
   * Return 0 on success, throws SDLError otherwise.
   */
  int set_draw_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  /* Draw a line from point (x1, y1) to (x2, y2).
   * Return 0 on success, throws SDLError otherwise.
   */
  int draw_line(int x1, int y1, int x2, int y2);

  /* Manually update the rendering. */
  void update();

  int get_width() const;
  int get_height() const;
  SDL_Renderer* get_renderer();
};

#endif
