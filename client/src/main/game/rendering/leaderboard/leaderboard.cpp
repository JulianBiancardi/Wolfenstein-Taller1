#include "leaderboard.h"

#include <iostream>
#include <utility>

#include "../../../../../../common/src/main/ids/images_ids.h"

#define PREFEER_WIDTH 320
#define PREFEER_HEIGHT 200

bool _compare_by_kills(const std::shared_ptr<Player>& p1,
                       const std::shared_ptr<Player>& p2) {
  return p1->get_kills() < p2->get_kills();
}

Leaderboard::Leaderboard(const Window& window, ResourceManager& res_manager)
    : window(window),
      res_manager(res_manager),
      scale_x(window.get_width() / PREFEER_WIDTH),
      scale_y(window.get_height() / PREFEER_HEIGHT) {
  _show_background();
}

Leaderboard::~Leaderboard() = default;

void Leaderboard::showTop5(std::vector<std::shared_ptr<Player>>&& players) {
  std::sort(players.begin(), players.end(), _compare_by_kills);

  SDL_Delay(5000);  // Todo fix this
}

void Leaderboard::_show_background() {
  Image* background = res_manager.get_image(LB_BACKGROUND);
  SDL_Rect rect_pos;
  rect_pos.x = 0;
  rect_pos.y = 0;
  rect_pos.w = window.get_width() * scale_x;
  rect_pos.h = window.get_height() * scale_y;
  background->draw(&rect_pos, nullptr);
}
