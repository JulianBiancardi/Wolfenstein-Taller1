#ifndef EVENT_H
#define EVENT_H

class Event {
 private:
  /* data */
 public:
  Event(/* args */);
  ~Event();

  virtual void operator()() = 0;
};

Event::Event() {}

Event::~Event() {}

#endif
