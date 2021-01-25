#include "match_maker.h"

#include "../../../../common/src/main/packets/packing.h"

MatchMaker::MatchMaker(Server& server, Window& window)
    : server(server), caster(window) {}

MatchMaker::~MatchMaker() {}

Match MatchMaker::join_match() {
  unsigned char packet[1];
  size_t size = pack(packet, "CC", REQUEST_MATCHES, server.get_id());
  Packet request_matches_packet() server.send();
  while (1) {
    handle_events();

    // Receive events
    // MovementEvent movement_event;
    // movement_event.setCaster(caster);
    // movement_event.process();

    update();
    render();
    frame_limiter.sleep();
  }
}

void handle_events();