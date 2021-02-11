#ifndef FRAME_LIMITER_H
#define FRAME_LIMITER_H

#include <cstddef>

class FrameLimiter {
 private:
  long frame_start;
  size_t iteration;
  int fps;
  int frame_rate;

 public:
  FrameLimiter();

  void sleep();

  ~FrameLimiter();
};

#endif
