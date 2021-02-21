#include "laderboard.h"

#include <iostream>

#define PREFEER_WIDTH 320
#define PREFEER_HEIGHT 200

LaderBoard::LaderBoard(SDL_Renderer *renderer, const Window &window)
    : renderer(renderer),
      window(window),
      scale_x(window.get_width() / PREFEER_WIDTH),
      scale_y(window.get_height() / PREFEER_HEIGHT),
      background(renderer, "") {}

LaderBoard::~LaderBoard() {}

void LaderBoard::showTop5() {}