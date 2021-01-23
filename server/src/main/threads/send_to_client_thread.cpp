#include "send_to_client_thread.h"

#include <syslog.h>

#include <utility>

#include "../../../../common/src/main/packets/packing.h"

SendToClientThread::SendToClientThread(unsigned int client_id,
                                       Socket& connected_socket,
                                       BlockingQueue<Packet>& events_queue)
    : client_id(client_id),
      connected_socket(connected_socket),
      events_queue(events_queue),
      allowed_to_run(true),
      running(false) {}

SendToClientThread::~SendToClientThread() {}

void SendToClientThread::force_stop() {
  allowed_to_run = false;
  unsigned char data[3];

  size_t size = pack(data, "CI", END_OF_CONNECTION, client_id);
  Packet disconnection_packet(size, data);
  events_queue.enqueue(disconnection_packet);
}

bool SendToClientThread::is_running() { return running; }

void SendToClientThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      Packet packet;
      events_queue.dequeue(packet);
      connected_socket.send((char*)&packet, sizeof(packet));
    }
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Unknown error");
  }
}
