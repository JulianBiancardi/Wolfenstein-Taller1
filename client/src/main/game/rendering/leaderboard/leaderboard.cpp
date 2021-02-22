#include "leaderboard.h"

#include <iostream>
#include <utility>

#include "../../../../../../common/src/main/ids/images_ids.h"

#define FIRST_Y_POS 16
#define POSITION_X_POS 78
#define POINTS_X_POS 108

bool _compare_by_points(const std::shared_ptr<Player>& p1,
                        const std::shared_ptr<Player>& p2) {
  return p1->get_points() > p2->get_points();
}

Leaderboard::Leaderboard(Window& window, ResourceManager& res_manager)
    : window(window),
      res_manager(res_manager),
      scale_x(window.get_width() / PREFEER_WIDTH),
      scale_y(window.get_height() / PREFEER_HEIGHT) {
  number_frame_w =
      (res_manager.get_image(HUD_NUMBER)->get_width() - 9 * PIXEL) /
      NUMBER_FRAME_X_COUNT;
  number_frame_h = res_manager.get_image(HUD_NUMBER)->get_height();
  number2_frame_w =
      (res_manager.get_image(GREEN_NUMBERS)->get_width() - 9 * PIXEL) /
      NUMBER_FRAME_X_COUNT;
  number2_frame_h = res_manager.get_image(GREEN_NUMBERS)->get_height();
}

Leaderboard::~Leaderboard() = default;

void Leaderboard::showTop5(std::vector<std::shared_ptr<Player>>&& players,
                           unsigned int player_id) {
  std::sort(players.begin(), players.end(), _compare_by_points);

  _show_background();

  for (unsigned int pos = 0; (pos < players.size()) && (pos < 5); pos++) {
    // Only show the top 5 players
    _show_player_data(players.at(pos), pos);
  }

  window.update();
  SDL_Delay(6000);
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

void Leaderboard::_show_player_data(const std::shared_ptr<Player>& player,
                                    unsigned int position) {
  int points = player->get_points();

  int cent_mil = points / 100000;
  int dec_mil = (points - (cent_mil * 100000)) / 10000;
  int mil = (points - (cent_mil * 100000 + dec_mil * 10000)) / 1000;
  int centenas =
      (points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000)) / 100;
  int decenas = (points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000 +
                           centenas * 100)) /
                10;
  int unidades = points - (cent_mil * 100000 + dec_mil * 10000 + mil * 1000 +
                           centenas * 100 + decenas * 10);

  SDL_Rect rect_pos;
  rect_pos.x = POINTS_X_POS * scale_x;
  rect_pos.y = (FIRST_Y_POS + position * 20) * scale_y;
  rect_pos.w = number_frame_w * scale_x;
  rect_pos.h = number_frame_h * scale_y;

  rect_pos.x = POSITION_X_POS * scale_x;
  _show_number(position + 1, &rect_pos);

  rect_pos.x = POINTS_X_POS * scale_x;
  _show_number2(cent_mil, &rect_pos);

  rect_pos.x = (POINTS_X_POS + 1 * (number_frame_w + PIXEL)) * scale_x;
  _show_number2(dec_mil, &rect_pos);

  rect_pos.x = (POINTS_X_POS + 2 * (number_frame_w + PIXEL)) * scale_x;
  _show_number2(mil, &rect_pos);

  rect_pos.x = (POINTS_X_POS + 3 * (number_frame_w + PIXEL)) * scale_x;
  _show_number2(centenas, &rect_pos);

  rect_pos.x = (POINTS_X_POS + 4 * (number_frame_w + PIXEL)) * scale_x;
  _show_number2(decenas, &rect_pos);

  rect_pos.x = (POINTS_X_POS + 5 * (number_frame_w + PIXEL)) * scale_x;
  _show_number2(unidades, &rect_pos);
}

void Leaderboard::_show_number(int number, SDL_Rect* position) {
  Image* number_image = res_manager.get_image(HUD_NUMBER);
  int sprite_x = number % NUMBER_FRAME_X_COUNT;
  SDL_Rect rect_slice = {(sprite_x * (number_frame_w + PIXEL)), 0,
                         number_frame_w, number_frame_h};
  number_image->draw(position, &rect_slice);
}

void Leaderboard::_show_number2(int number, SDL_Rect* position) {
  Image* number_image = res_manager.get_image(GREEN_NUMBERS);
  int sprite_x = number % NUMBER_FRAME_X_COUNT;
  SDL_Rect rect_slice = {(sprite_x * (number2_frame_w + PIXEL)), 0,
                         number2_frame_w, number2_frame_h};
  number_image->draw(position, &rect_slice);
}