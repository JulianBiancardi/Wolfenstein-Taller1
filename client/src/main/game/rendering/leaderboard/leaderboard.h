#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <memory>
#include <vector>

#include "../../entities/player.h"
#include "../sdl/image.h"
#include "../sdl/window.h"

class Leaderboard {
 private:
  Window &window;
  ResourceManager &res_manager;
  TTF_Font *font;
  unsigned int player_id;
  bool victory;
  int scale_x;
  int scale_y;
  int number_frame_w;
  int number_frame_h;
  int number2_frame_w;
  int number2_frame_h;

  void _show_background();
  void _show_bottom_banner();
  void _show_titles();

  void _show_player_points(const std::shared_ptr<Player> &player,
                           unsigned int position);
  void _show_player_kills(const std::shared_ptr<Player> &player,
                          unsigned int position);

  void _show_game_result();

 public:
  Leaderboard(Window &window, ResourceManager &res_manager,
              unsigned int player_id);
  ~Leaderboard();

  void showTop5(std::vector<std::shared_ptr<Player>> &&players);
};

#endif  // LEADERBOARD_H