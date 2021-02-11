#include "frame_limiter.h"

#include <SDL2/SDL.h>

#include "../../../../../common/src/main/config_loader.h"

FrameLimiter::FrameLimiter()
    : frame_start(SDL_GetTicks()),
      iteration(0),
      fps(CL::fps),
      frame_rate(1000 / fps) {}

void FrameLimiter::sleep() {
  long long frame_time, rest_time, behind, lost;
  frame_time = SDL_GetTicks();

  rest_time = frame_rate - (frame_time - frame_start);
  if (rest_time < 0) {
    behind = -rest_time;  // this is always positive
    rest_time = frame_rate - behind % frame_rate;
    lost = behind + rest_time;
    frame_start += lost;
    iteration += floor(double(lost / frame_rate));  // floor division
  }

  SDL_Delay(rest_time);
  frame_start += frame_rate;
  iteration++;
}

FrameLimiter::~FrameLimiter() {}
