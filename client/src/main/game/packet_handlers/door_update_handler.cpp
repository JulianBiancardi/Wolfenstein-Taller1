#include "door_update_handler.h"

#include "../../../../../common/src/main/packets/packing.h"

DoorUpdateHandler::DoorUpdateHandler() {}

DoorUpdateHandler::~DoorUpdateHandler() {}

bool DoorUpdateHandler::handle(Packet& packet, Map& map, GameSound& sound) {
  unsigned char type;
  unsigned int player_id;
  unsigned char match_id;
  unsigned int x_pos;
  unsigned int y_pos;
  bool state;
  unpack(packet.get_data(), "CICIIC", &type, &player_id, &match_id, &x_pos,
         &y_pos, &state);

  if (map.set_door_state(std::make_pair(x_pos, y_pos), state)) {
    Point door_pos(x_pos + 0.5, y_pos + 0.5);
    if (state) {
      sound.play_door(
          door_pos, 30);  // FIXME Update, move somewhere else, like a sound_ids
    } else {
      sound.play_door(door_pos, 31);  // FIXME Idem
    }
  }

  return true;
}
