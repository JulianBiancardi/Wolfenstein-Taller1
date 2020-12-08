#ifndef CASTER_H
#define CASTER_H

#include <SDL2/SDL.h>

#include "map.h"
#include "resource_manager.h"
#include "sdl/window.h"
#include "utils/ray.h"

class Caster {
 private:
  SDL_Renderer* renderer;
  Ray& player;
  Map& map;
  Window& window;
  ResourceManager res_manager;

  void draw_background();
  std::vector<Point> get_wall_collisions();
  void draw(std::vector<Point> wall_collisions);

 public:
  Caster(Window& window, Ray& player, Map& map);
  ~Caster();

  void operator()();
};

#endif
