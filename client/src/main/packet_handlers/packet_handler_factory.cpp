#include "packet_handler_factory.h"

#include "../../../../common/src/main/packets/packet.h"
#include "../../../../common/src/main/packets/packet_handler_factory_error.h"
#include "change_gun_handler.h"
#include "movement_handler.h"
#include "rotation_handler.h"
#include "shot_handler.h"
#include "spawn_player_handler.h"

PacketHandler* PacketHandlerFactory::build(Packet& packet) {
  switch (packet.get_type()) {
      // TODO FIX This once all have been defined
    case MOVEMENT:
      return new MovementHandler();
    case ROTATION:
      return new RotationHandler();
    case SHOT:
      return new ShotHandler();
    case CHANGE_GUN:
      return new ChangeGunHandler();
    case SPAWN_PLAYER:
      return new SpawnPlayerHandler();
    /*
    case DOOR_PACKET:
      return new nullptr;  // TODO
    case DAMAGE_PACKET:
      return new DamageHandler(who, enemy_hit,
    event.data.shot.damage_done); case GAME_OVER_PACKET: return new
    GameOverHandler();
      */
    default:
      printf("Undetected Packet Type: %u\n", packet.get_type());
      throw PacketHandlerFactoryError("Packet type is not valid. Type is %u.",
                                      packet.get_type());
      break;
  }
}