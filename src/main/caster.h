#ifndef CASTER_H
#define CASTER_H

#include <SDL2/SDL.h>

#include "collision.h"
#include "map.h"
#include "resource_manager.h"
#include "sdl/window.h"
#include "utils/ray.h"

// ============================

class _sprite {
 private:
  Point pos;
  double distance;

 public:
  _sprite(Point pos) : pos(pos), distance(0) {}
  ~_sprite() {}
  void update_distance(Point src);
  double get_distance();
};

// ============================

class Caster {
 private:
  SDL_Renderer* renderer;
  Ray& player;
  Map& map;
  Window& window;
  ResourceManager res_manager;

  void draw_background();

  std::vector<double> draw_walls();
  void draw_wall(Collision& collision, size_t screen_pos, double ray_angle);

  void draw_sprites(std::vector<double>& wall_distances);

  double get_projected_distance(double ray_angle, double player_angle,
                                double collision_distance);
  // TODO Review this code
  void sort_sprites(std::vector<_sprite>& sprites);

 public:
  Caster(Window& window, Ray& player, Map& map);
  ~Caster();

  void operator()();
};

#endif
