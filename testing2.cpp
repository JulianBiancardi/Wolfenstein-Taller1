#include <SDL2/SDL.h>

#include <iostream>

#include "src/main/sdl/window.h"

#define UNIT 5
#define SCREEN_WIDTH (320 * UNIT)
#define SCREEN_HEIGHT (200 * UNIT)

int main(int argc, char** argv) {
  Window window("Bitmap Testing", SCREEN_WIDTH, SCREEN_HEIGHT);
  window.fill(255, 255, 255, 255);

  SDL_Surface* window_surface = window.get_surface();

  // TODO Wrap image
  SDL_Surface* image = SDL_LoadBMP("res/walls/grey_brick_wall.bmp");

  if (image == NULL) {
    return 1;
  }

  // TODO Use this to slice image
  SDL_Rect slice;
  // Top left of slice
  slice.x = 0;
  slice.y = 0;
  // Distance to bot right of slice
  slice.w = 64;
  slice.h = 64;

  SDL_Rect pos;
  // This positions
  pos.x = 0;
  pos.y = 0;
  // This stretches if it doesn't match rect1 w and h
  pos.w = 64;
  pos.h = 64;

  SDL_Rect rect3;
  rect3.x = 10;
  rect3.y = 74;
  rect3.w = 64;
  rect3.h = 64;

  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(window.get_renderer(), image);
  SDL_RenderCopy(window.get_renderer(), texture, &slice, &pos);
  SDL_RenderCopy(window.get_renderer(), texture, NULL, &rect3);
  window.update();
  SDL_Delay(5000);

  SDL_FreeSurface(image);

  return 0;
}