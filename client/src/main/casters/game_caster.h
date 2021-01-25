#ifndef GAME_CASTER_H
#define GAME_CASTER_H

#include <SDL2/SDL.h>

#include "../../../common/src/main/utils/ray.h"
#include "casting/collision.h"
#include "map.h"
#include "resource_manager.h"
#include "sdl/window.h"

// ============================

class _sprite {
 private:
  Point pos;
  double distance;
  int id;

 public:
  _sprite(Point pos, int id) : pos(pos), distance(0), id(id) {}
  ~_sprite() {}
  void update_distance(Point src);
  double get_distance();
  Point get_pos() { return pos; }
  int get_id();
};

// ============================

#include "caster.h"

class GameCaster : public Caster {
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
  void draw_sprite(_sprite& sprite, std::vector<double>& wall_distances);

  double get_projected_distance(double ray_angle, double player_angle,
                                double collision_distance);
  // TODO Review this code
  void sort_sprites(std::vector<_sprite>& sprites);

 public:
  GameCaster(Window& window, Ray& player, Map& map);
  ~GameCaster();

  void operator()() override;
};

#endif
