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
  TTF_Font *font;
  Image background;
  Image bj_faces;
  Image key;

  void _show_background(const Window &window) const;
  void _show_stats(const Window &window, const Player &player) const;
  void _show_face(const Window &window, const Player &player);
  void _show_key(const Window &window, const Player &player);
  void _show_gun(const Window &window, const Player &player) const;

 public:
  Hud(SDL_Renderer *renderer);
  ~Hud();

  void update(const Window &window, const Player &player);
};

#endif  // HUD_H