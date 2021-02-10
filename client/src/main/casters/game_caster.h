#ifndef GAME_CASTER_H
#define GAME_CASTER_H

#include <SDL2/SDL.h>

#include "../../../../common/src/main/utils/ray.h"
#include "../casting/collision.h"
#include "../hud/hud.h"
#include "../map.h"
#include "../resource_manager.h"
#include "../sdl/window.h"

class GameCaster {
 private:
  SDL_Renderer* renderer;
  Map& map;
  Window& window;
  ResourceManager res_manager;
  unsigned int player_id;
  Hud hud;

  void draw_background();

  std::vector<double> draw_walls();
  void draw_wall(Collision& collision, size_t screen_pos, double ray_angle);

  void draw_objects(std::vector<double>& wall_distances);
  void draw_object(Object& object, double distance,
                   std::vector<double>& wall_distances);

  double get_projected_distance(double ray_angle, double player_angle,
                                double collision_distance);

  void sort_objects(std::vector<std::shared_ptr<Object>>& objects,
                    std::vector<double>& distances);

 public:
  GameCaster(Window& window, Map& map, unsigned int player_id);
  ~GameCaster();

  void operator()();
};

#endif
