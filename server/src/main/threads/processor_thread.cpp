#include "processor_thread.h"

#include <memory>

#include "../events/event_handler_factory.h"

ProcessorThread::ProcessorThread(MatchManager& match_manager,
                                 ClientManager& client_manager,
                                 BlockingQueue<Packet>& reception_queue)
    : match_manager(match_manager),
      client_manager(client_manager),
      reception_queue(reception_queue) {}

ProcessorThread::~ProcessorThread() {}

void ProcessorThread::run() {
  while (allowed_to_run) {
    Packet packet;
    reception_queue.dequeue(packet);

    std::unique_ptr<EventHandler> handler(EventHandlerFactory::build(packet));
    handler->handle(client_manager, match_manager);
  }
}