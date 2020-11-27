#include <iostream>

#include "src/main/window.h"

int main(int argc, char** argv) {
  Window window("Hello World!", 320, 320);
  std::cout << window.fill(255, 0, 0, 255) << std::endl;
  std::cout << window.set_draw_color(0, 0, 0, 255) << std::endl;
  std::cout << window.draw_line(0, 0, 10, 10) << std::endl;
  std::cout << window.draw_line(0, 0, 20, 30) << std::endl;
  window.update();
  SDL_Delay(5000);
}