#include "packet_handler_factory.h"

#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packet_handler_factory_error.h"
#include "movement_handler.h"
#include "rotation_handler.h"

PacketHandler* PacketHandlerFactory::build(Packet& packet) {
  switch (packet.get_type()) {
      // TODO FIX This once all have been defined
    case MOVEMENT:
      return new MovementHandler();
    case ROTATION:
      return new RotationHandler();
    /*
    case DOOR_PACKET:
      return new nullptr;  // TODO
    case CHANGE_GUN_PACKET:
      return new ChangeGunHandler();
    case DAMAGE_PACKET:
      return new DamageHandler(who, enemy_hit, event.data.shot.damage_done);
    case GAME_OVER_PACKET:
      return new GameOverHandler();
      */
    default:
      throw PacketHandlerFactoryError("Packet type is not valid. Type is %u.",
                                      packet.get_type());
      break;
  }
}