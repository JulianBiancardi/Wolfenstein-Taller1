#ifndef SURFACE_H
#define SURFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Surface {
 private:
  SDL_Surface* surface;

 public:
  /*Constructor for images*/
  Surface(const std::string& file);
  /*Constructor for text*/
  Surface(const std::string& text, TTF_Font* font, SDL_Color& color);
  ~Surface();

  size_t get_width() const;
  size_t get_height() const;
  SDL_Surface* get_surface() const;
};

#endif
