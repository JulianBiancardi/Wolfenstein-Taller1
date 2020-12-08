#ifndef CASTER_H
#define CASTER_H

#include <SDL2/SDL.h>

#include "collision.h"
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
  std::vector<Collision> get_wall_collisions();
  void draw(std::vector<Collision>& wall_collisions);
  void draw_wall(Collision& collision, size_t screen_pos, double ray_angle);

  double get_projected_distance(double ray_angle, double player_angle,
                                double collision_distance);

 public:
  Caster(Window& window, Ray& player, Map& map);
  ~Caster();

  void operator()();
};

#endif
