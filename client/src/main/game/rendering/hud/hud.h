#ifndef HUD_H
#define HUD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../entities/player.h"
#include "../sdl/image.h"
#include "../sdl/window.h"

class Hud {
 private:
  SDL_Renderer *renderer;
  int scale_x;
  int scale_y;
  TTF_Font *font;
  Image background;
  Image bj_faces;
  Image key;
  Image numbers;
  int number_frame_w;
  int number_frame_h;

  void _show_background(const Window &window);
  void _show_stats(const Window &window, const Player &player);
  void _show_lives(const Window &window, const Player &player);
  void _show_points(const Window &window, const Player &player);
  void _show_health(const Window &window, const Player &player);
  void _show_bullets(const Window &window, const Player &player);
  void _show_face(const Window &window, const Player &player);
  void _show_key(const Window &window, const Player &player);
  void _show_gun(const Window &window, const Player &player);

  /*Show the number at position.The number must be betwen 0 to 9*/
  void _show_number(int number, SDL_Rect *position);

 public:
  Hud(SDL_Renderer *renderer);
  ~Hud();

  void update(const Window &window, const Player &player);
};

#endif  // HUD_H