#include "send_to_server_thread.h"

#include <syslog.h>

#include <utility>

SendToServerThread::SendToServerThread(Socket& connected_socket,
                                       BlockingQueue<Packet>& events_queue)
    : connected_socket(connected_socket),
      events_queue(events_queue),
      allowed_to_run(true),
      running(false) {}

SendToServerThread::~SendToServerThread() {}

void SendToServerThread::force_stop() {
  allowed_to_run = false;
  Packet disconnection_packet;
  // TODO Fill with disconnection info
  events_queue->enqueue(disconnection_packet);
}

bool SendToServerThread::is_running() { return running; }

void SendToServerThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      Packet packet;
      events_queue->dequeue(packet);
      connected_socket.send((char*)&packet, sizeof(packet));
    }
    running = false;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Unknown error");
  }
}
