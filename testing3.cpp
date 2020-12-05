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

  Point pos(0, 0);
  printf("pos_point:\n%d %d\n", (int)pos.getX(), (int)pos.getY());
  Rectangle slice(0, 64, 0, 64);

  Image image(window.get_renderer(), "res/walls/grey_brick_wall.bmp");
  image.draw(pos, slice);
  /*
    SDL_Rect rect3;
    rect3.x = 10;
    rect3.y = 74;
    rect3.w = 64;
    rect3.h = 64;
    SDL_Texture* texture = image.get_texture();
    SDL_RenderCopy(window.get_renderer(), texture, NULL, &rect3);*/

  window.update();
  SDL_Delay(5000);

  return 0;
}