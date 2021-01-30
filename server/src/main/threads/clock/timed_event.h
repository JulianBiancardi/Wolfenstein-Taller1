#ifndef TIMED_EVENT_H
#define TIMED_EVENT_H

#include <chrono>

class TimedEvent {
 private:
  std::chrono::duration<double> remaining_time;
  bool should_delete;

 protected:
  explicit TimedEvent(double duration);

 public:
  void update();
  virtual void execute() = 0;
  bool should_be_deleted() const;
  virtual ~TimedEvent();
};

#endif
