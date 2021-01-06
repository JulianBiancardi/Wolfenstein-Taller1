<<<<<<< HEAD
#ifndef WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_EVENT_H_
#define WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_EVENT_H_
#include "../../../../common/src/main/utils/ray.h"
//#include "../caster.h"
#include "../stage.h"
#include <utility>
#include <memory>
#include <vector>

class Event {
 protected:
  Stage& stage;
 public:

  Event(Stage& stage);
  static std::unique_ptr<Event> create(Stage& Stage/*, SocketReceiver& socket*/);
  virtual ~Event() {};
  virtual void process()=0;

};

#endif //WOLFENSTEIN_TALLER1_CLIENT_SRC_MAIN_EVENTS_EVENT_H_
=======
    /*
#ifndef EVENT_H
#define EVENT_H

class Event {
 private:
  // data
 public:
  Event(// args );
  ~Event();

  virtual void operator()() = 0;
};

Event::Event() {}

Event::~Event() {}

#endif
     */
>>>>>>> 2cc3905b10235b096bbf9bf17d42ef1d8146e4eb
