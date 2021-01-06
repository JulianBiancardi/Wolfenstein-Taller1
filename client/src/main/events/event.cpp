#include "event.h"

Event::Event(int &stage) {
  //Socket
}

std::unique_ptr<Event> Event::create(Stage &Stage /*, EventInfo &eventInfo*/) {
  //std::vector<int> event;
  //socket.receive(event);
  //socket.receive...
  switch (event.type) {
    case 1: //TODO Use constants
//      return move_event(doer, event.data.point.x, event.data.point.y);
      return std::unique_ptr<event>(new MovementEvent(event.player_id, event.data.point));
    default: throw -1; //TODO Throw ours exception
  }

}