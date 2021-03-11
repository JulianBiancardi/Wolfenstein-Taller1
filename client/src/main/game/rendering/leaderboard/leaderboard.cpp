#include "leaderboard.h"

#include <iostream>
#include <utility>

#include "../../../../../../common/src/main/config_loader.h"
#include "../../../../../../common/src/main/ids/images_ids.h"
#include "../../../../../../common/src/main/paths.h"
#include "../sdl/text.h"

#define FONT_PATH "fonts/Montserrat-Regular.ttf"
#define FONT_SIZE 14

#define TITLES_X_POS 88
#define TITLES_Y_POS 16
#define FIRST_Y_POS 36
#define POSITION_X_POS 68
#define POINTS_X_POS 108
#define KILLS_X_POS 208
#define RESULT_X_POS 132
#define RESULT_Y_POS 174

bool _compare_by_points(const std::shared_ptr<Player>& p1,
                        const std::shared_ptr<Player>& p2) {
  return p1->get_points() > p2->get_points();
}
bool _compare_by_kills(const std::shared_ptr<Player>& p1,
                       const std::shared_ptr<Player>& p2) {
  return p1->get_kills() > p2->get_kills();
}

Leaderboard::Leaderboard(Window& window, ResourceManager& res_manager,
                         unsigned int player_id)
    : window(window),
      res_manager(res_manager),
      player_id(player_id),
      victory(false),
      scale_x(window.get_width() / PREFEER_WIDTH),
      scale_y(window.get_height() / PREFEER_HEIGHT) {
  font = TTF_OpenFont(asset_path(FONT_PATH).c_str(), FONT_SIZE * scale_x);
}

Leaderboard::~Leaderboard() = default;

void Leaderboard::showTop5(std::vector<std::shared_ptr<Player>>&& players) {
  _show_background();
  _show_bottom_banner();
  _show_titles();

  std::sort(players.begin(), players.end(), _compare_by_points);
  if (players.at(0)->get_id() == player_id) {
    victory = true;
  }

  for (unsigned int pos = 0; (pos < players.size()) && (pos < 5); pos++) {
    // Only show the top 5 players
    _show_player_points(players.at(pos), pos);
  }

  std::sort(players.begin(), players.end(), _compare_by_kills);
  for (unsigned int pos = 0; (pos < players.size()) && (pos < 5); pos++) {
    // Only show the top 5 players
    _show_player_kills(players.at(pos), pos);
  }

  _show_game_result();

  window.update();
  SDL_Delay(CL::leaderboard * 1000);
}

void Leaderboard::_show_background() {
  Image* background = res_manager.get_image(LB_BACKGROUND);
  SDL_Rect rect_pos;
  rect_pos.x = 0;
  rect_pos.y = 0;
  rect_pos.w = window.get_width();
  rect_pos.h = window.get_height();

  background->draw(&rect_pos, nullptr);
}

void Leaderboard::_show_bottom_banner() {
  Image* bottom_banner = res_manager.get_image(LB_BOTTOM_BANNER);
  SDL_Rect rect_pos;
  rect_pos.x = 0;
  rect_pos.y = (window.get_height() - bottom_banner->get_height() * scale_y);
  rect_pos.w = window.get_width();
  rect_pos.h = bottom_banner->get_height() * scale_y;

  bottom_banner->draw(&rect_pos, nullptr);
}

void Leaderboard::_show_titles() {
  SDL_Color white = {255, 255, 255};
  Text titles_points(window.get_renderer(), "Points", font, white);
  titles_points.draw(TITLES_X_POS * scale_x, TITLES_Y_POS * scale_y);

  Text titles_kills(window.get_renderer(), "Kills", font, white);
  titles_kills.draw((TITLES_X_POS + 112) * scale_x, TITLES_Y_POS * scale_y);
}

void Leaderboard::_show_player_points(const std::shared_ptr<Player>& player,
                                      unsigned int position) {
  SDL_Color color = {0, 140, 115};

  Text position_text(window.get_renderer(), std::to_string(position + 1), font,
                     color);

  color = {255, 255, 255};
  if (player->get_id() == player_id) {
    color = {255, 255, 0};
  }
  Text points_text(window.get_renderer(), std::to_string(player->get_points()),
                   font, color);

  position_text.draw(POSITION_X_POS * scale_x,
                     (FIRST_Y_POS + position * 20) * scale_y);
  points_text.draw(POINTS_X_POS * scale_x,
                   (FIRST_Y_POS + position * 20) * scale_y);
}

void Leaderboard::_show_player_kills(const std::shared_ptr<Player>& player,
                                     unsigned int position) {
  SDL_Color color = {255, 255, 255};
  if (player->get_id() == player_id) {
    color = {255, 255, 0};
  }
  Text kills_text(window.get_renderer(), std::to_string(player->get_kills()),
                  font, color);
  kills_text.draw(KILLS_X_POS * scale_x,
                  (FIRST_Y_POS + position * 20) * scale_y);
}

void Leaderboard::_show_game_result() {
  Image* face;
  SDL_Color color;

  if (victory == true) {
    color = {255, 255, 0};
    Text status(window.get_renderer(), "Victory", font, color);
    status.draw(RESULT_X_POS * scale_x, RESULT_Y_POS * scale_y);
    face = res_manager.get_image(LB_VICTORY);
  } else {
    color = {255, 0, 0};
    Text status(window.get_renderer(), "Defeat", font, color);
    status.draw(RESULT_X_POS * scale_x, RESULT_Y_POS * scale_y);
    face = res_manager.get_image(LB_DEFEAT);
  }

  SDL_Rect rect_pos;
  rect_pos.x = window.get_width() - (20 * scale_x);
  rect_pos.y = window.get_height() - (24 * scale_y);
  rect_pos.w = (face->get_width() * scale_x) / 2;
  rect_pos.h = (face->get_height() * scale_y) / 2;
  face->draw(&rect_pos, nullptr);
}