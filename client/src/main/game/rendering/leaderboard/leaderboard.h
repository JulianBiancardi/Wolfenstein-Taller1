#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "../../entities/player.h"
#include "../sdl/image.h"
#include "../sdl/window.h"

class Leaderboard {
 private:
  const Window &window;
  ResourceManager &res_manager;
  int scale_x;
  int scale_y;

  void _show_background();
  void _show_player_data();

 public:
  Leaderboard(const Window &window, ResourceManager &res_manager);
  ~Leaderboard();

  void showTop5(std::vector<std::shared_ptr<Player>> &&players);
};

#endif  // LEADERBOARD_H