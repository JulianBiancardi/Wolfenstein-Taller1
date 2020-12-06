#include <SDL2/SDL.h>

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
  Rectangle slice(0, 8, 0, 8);

  std::string source("res/walls/grey_brick_wall.bmp");
  Image image(window.get_renderer(), source);
  image.draw(pos0, NULL);
  image.draw(pos1, &slice, 8, 8);
  image.draw(pos2, NULL);
  image.draw(pos3, NULL);

  window.update();
  SDL_Delay(500);

  return 0;
}