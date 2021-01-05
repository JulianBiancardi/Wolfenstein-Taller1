#include "movement_event.h"

MovementEvent::MovementEvent(const int &id, const int &new_origin) :
                id(id), new_origin(new_origin) {}

void MovementEvent::process() {
  //Se procesa el evento. Todos los eventos deberían entender el mensaje process()

}