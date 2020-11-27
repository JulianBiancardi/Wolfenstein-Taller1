#include <iostream>

#include "src/main/window.h"

int main(int argc, char** argv) {
  Window window("Hello World!", 320, 320);
  std::cout << window.set_draw_color(255, 0, 0, 255) << std::endl;
  std::cout << window.clear() << std::endl;
  std::cout << window.fill(255, 0, 0, 255) << std::endl;
  SDL_Delay(5000);
}