#include "send_to_client_thread.h"

#include <syslog.h>

#include <utility>

SendToClientThread::SendToClientThread(Socket& connected_socket,
                                       BlockingQueue<packet_t>& events_queue)
    : connected_socket(connected_socket),
      events_queue(events_queue),
      allowed_to_run(true),
      running(false) {}

SendToClientThread::~SendToClientThread() {}

void SendToClientThread::force_stop() {
  allowed_to_run = false;
  packet_t disconnection_packet;
  // TODO Fill with disconnection info
  events_queue.enqueue(disconnection_packet);
}

void SendToClientThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      packet_t packet;
      events_queue.dequeue(packet);
      connected_socket.send((char*)&packet, sizeof(packet));
    }
    running = false;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Unknown error");
  }
}
