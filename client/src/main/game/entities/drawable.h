#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../rendering/resource_manager.h"
#include "../rendering/sdl/image.h"

class Drawable {
 private:
 public:
  Drawable();
  ~Drawable();

  /* Returns an image associated with the drawable. */
  virtual Image* get_image(ResourceManager& resource_manager) = 0;
};

#endif
