#include "processor_thread.h"

#include <memory>

#include "../packet_handlers/packet_handler.h"
#include "../packet_handlers/packet_handler_factory.h"

ProcessorThread::ProcessorThread(ClientManager& client_manager)
    : match_manager(), client_manager(client_manager) {}

ProcessorThread::~ProcessorThread() {}

void ProcessorThread::run() {
  BlockingQueue<Packet>& reception_queue = client_manager.get_reception_queue();
  while (allowed_to_run) {
    Packet packet;
    reception_queue.dequeue(packet);

    std::unique_ptr<PacketHandler> handler(PacketHandlerFactory::build(packet));
    handler->handle(packet, client_manager, match_manager);
  }
}