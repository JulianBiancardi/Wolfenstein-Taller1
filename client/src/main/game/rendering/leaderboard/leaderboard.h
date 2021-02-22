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
  Window &window;
  ResourceManager &res_manager;
  int scale_x;
  int scale_y;
  int number_frame_w;
  int number_frame_h;
  int number2_frame_w;
  int number2_frame_h;

  void _show_background();
  void _show_player_data(const std::shared_ptr<Player> &player,
                         unsigned int position);

  /*Show the number at position.The number must be betwen 0 to 9*/
  void _show_number(int number, SDL_Rect *position);

  /*Show the number at position.The number must be betwen 0 to 9*/
  void _show_number2(int number, SDL_Rect *position);

 public:
  Leaderboard(Window &window, ResourceManager &res_manager);
  ~Leaderboard();

  void showTop5(std::vector<std::shared_ptr<Player>> &&players,
                unsigned int player_id);
};

#endif  // LEADERBOARD_H