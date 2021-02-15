#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL2/SDL.h>

#include "../rendering/resource_manager.h"
#include "../rendering/sdl/image.h"

class Drawable {
 protected:
  SDL_Rect slice;

 public:
  Drawable();
  ~Drawable();

  /* Returns an image associated with the drawable. */
  virtual Image* get_image(ResourceManager& resource_manager) = 0;

  /* Returns the slice of the image to be drawn. */
  virtual SDL_Rect* get_slice(void* extra);
};

#endif
