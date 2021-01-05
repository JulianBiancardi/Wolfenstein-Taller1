#include "event.h"

Event::Event(int &stage) {
  //Socket
}

std::unique_ptr<Event> Event::create(Stage &Stage) {
  //std::vector<int> event;
  //socket.receive(event);
  //socket.receive...
  //int msg_type = event[0];


  switch (event.type) {
    case 1: //TODO Use constants
      return move_event(doer, event.data.point.x, event.data.point.y);
      break;

    default: throw -1; //TODO Throw ours exception
  }

  switch (msg_type) {
    case MSG_CAR_ID:
      return std::unique_ptr<event>(new CarID(event[1], scenario));
    case MSG_SET_HEALTH:
      return std::unique_ptr<event>(new SetCarHealth(scenario, event[1], command[2]));
    default:
      return std::unique_ptr<event>(nullptr);
  }
  return std::unique_ptr<event>(nullptr);


}