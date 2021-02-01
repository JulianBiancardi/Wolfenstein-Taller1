#ifndef FRAME_LIMITER_H
#define FRAME_LIMITER_H

#include <SDL2/SDL.h>

#include "iostream"  //TODO delete

#define FPS 30                   // TODO move to congif file
#define FRAME_RATE (1000 / FPS)  // TODO move to congif file

//-------------------------------------
class FrameLimiter {
 private:
  Uint32 frame_start;
  size_t iteration = 0;

 public:
  FrameLimiter();

  void sleep();

  ~FrameLimiter();
};

FrameLimiter::FrameLimiter() : frame_start(SDL_GetTicks()) {}

void FrameLimiter::sleep() {
  Uint32 frame_time, rest_time, behind, lost;
  frame_time = SDL_GetTicks();

  rest_time = FRAME_RATE - (frame_time - frame_start);
  if (rest_time < 0) {
    behind = -rest_time;  // this is always positive
    rest_time = FRAME_RATE - behind % FRAME_RATE;
    lost = behind + rest_time;
    frame_start += lost;
    iteration += floor(double(lost / FRAME_RATE));  // floor division
  }

  std::cout << "FPS: " << 1000 / rest_time << std::endl;
  SDL_Delay(rest_time);
  frame_start += FRAME_RATE;
  iteration++;
}

FrameLimiter::~FrameLimiter() {}

#endif  // FRAME_LIMITER_H