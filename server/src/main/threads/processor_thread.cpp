#include "processor_thread.h"

#include <syslog.h>

#include <memory>

#include "../../../../common/src/main/packets/packet_error.h"
#include "../packet_handlers/packet_handler.h"
#include "../packet_handlers/packet_handler_factory.h"

ProcessorThread::ProcessorThread(ClientManager& client_manager)
    : match_manager(), client_manager(client_manager), allowed_to_run(true) {}

ProcessorThread::~ProcessorThread() {}

void ProcessorThread::force_stop() {
  allowed_to_run = false;
  client_manager.get_reception_queue().enqueue(Packet());
}

void ProcessorThread::run() {
  BlockingQueue<Packet>& reception_queue = client_manager.get_reception_queue();
  while (allowed_to_run) {
    Packet packet;
    reception_queue.dequeue(packet);

    try {
      std::unique_ptr<PacketHandler> handler(
          PacketHandlerFactory::build(packet));
      handler->handle(packet, client_manager, match_manager);
    } catch (const PacketError& e) {
      syslog(LOG_ERR, "Packet received hasn't got a valid type.");
    }  // TODO catch other errors
  }
}