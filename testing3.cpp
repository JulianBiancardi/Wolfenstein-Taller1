#include <SDL2/SDL.h>

#include <iostream>  // TODO Delete

#include "src/main/point.h"
#include "src/main/rectangle.h"
#include "src/main/sdl/image.h"
#include "src/main/sdl/window.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

int main(int argc, char** argv) {
  Window window("Bitmap Testing", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.fill(255, 255, 255, 255);

  Point pos0(0, 0);
  Point pos1(64, 64);
  Point pos3(64, 0);
  Point pos2(0, 64);
  Rectangle slice(0, 64, 0, 64);

  std::string source("res/walls/grey_brick_wall.bmp");
  Image image(window.get_renderer(), source);
  image.draw(pos0, &slice);
  image.draw(pos1, &slice, 6, 6);
  image.draw(pos2, &slice);
  image.draw(pos3, &slice);

  window.update();
  SDL_Delay(5000);

  return 0;
}