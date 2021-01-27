#include "packet_handler_factory.h"

#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packet_error.h"
#include "change_gun_handler.h"
#include "move_handler.h"
#include "request_matches_handler.h"

PacketHandler* PacketHandlerFactory::build(Packet& packet) {
  switch (packet.get_type()) {
    case REQUEST_MATCHES:
      return new RequestMatchesHandler();
    case MOVE_PACKET:
      return new MoveHandler();
    case ROTATE_PACKET:
      return new nullptr;  // TODO
    case DOOR_PACKET:
      return new nullptr;  // TODO
    case CHANGE_GUN_PACKET:
      return new ChangeGunHandler();
    case DAMAGE_PACKET:
      return new DamageHandler(who, enemy_hit, event.data.shot.damage_done);
    case GAME_OVER_PACKET:
      return new GameOverHandler();
    default:
      throw PacketError("Packet type is not valid. Type is %u.",
                        packet.get_type());
      break;
  }
}