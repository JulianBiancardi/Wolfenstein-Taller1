#include "processor_thread.h"

#include <syslog.h>

#include <memory>

#include "../../../../common/src/main/packets/packet_handler_factory_error.h"
#include "../managers/match_error.h"
#include "../managers/match_manager_error.h"
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
  try {
    BlockingQueue<Packet>& reception_queue =
        client_manager.get_reception_queue();
    while (allowed_to_run) {
      Packet packet;
      reception_queue.dequeue(packet);

      try {
        std::unique_ptr<PacketHandler> handler(
            PacketHandlerFactory::build(packet));
        handler->handle(packet, client_manager, match_manager);
      } catch (const MatchError& e) {
        syslog(
            LOG_NOTICE,
            "[ERROR] ProcessorThread - Notice: Invalid operation in packet - "
            "%s\n",
            e.what());
      } catch (const MatchManagerError& e) {
        syslog(
            LOG_NOTICE,
            "[ERROR] ProcessorThread - Notice: Invalid operation in packet - "
            "%s\n",
            e.what());
      } catch (const PacketHandlerFactoryError& e) {
        syslog(LOG_ERR, "[ERROR] ProcessorThread - Error: %s\n", e.what());
      }
    }

  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] ProcessorThread - Error: %s", e.what());
    printf("ProcessorThread: %s\n", e.what());  // TODO DELETE
  } catch (...) {
    syslog(LOG_ERR, "[Error] ProcessorThread - Unknown error");
  }
}