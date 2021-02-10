#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "surface.h"

class Texture {
 private:
  SDL_Texture* texture;
  Surface surface;

 public:
  /*Constructor for images*/
  Texture(SDL_Renderer* renderer, const std::string& image);
  /*Constructor for text*/
  Texture(SDL_Renderer* renderer, const std::string& text, TTF_Font* font,
          SDL_Color& color);

  ~Texture();

  Texture(const Texture&) = delete;              // No copy constructor
  Texture& operator=(const Texture&) = delete;   // No copy constructor
  Texture(Texture&& other) = delete;             // No move constructor
  Texture& operator=(Texture&& other) = delete;  // No move constructor

  size_t get_width() const;
  size_t get_height() const;
  SDL_Texture* get_texture() const;
};

#endif
