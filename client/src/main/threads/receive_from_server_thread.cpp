#include "receive_from_server_thread.h"

#include <syslog.h>

ReceiveFromServerThread::ReceiveFromServerThread(
    Socket& connected_socket, ProtectedQueue<Packet>& reception_queue)
    : connected_socket(connected_socket),
      reception_queue(reception_queue),
      allowed_to_run(true),
      running(false) {}

ReceiveFromServerThread::~ReceiveFromServerThread() {}

bool ReceiveFromServerThread::is_running() { return running; }

void ReceiveFromServerThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      Packet packet;
      connected_socket.receive((char*)&packet, sizeof(Packet));
      reception_queue->enqueue(packet);
    }
    running = false;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Unknown error");
  }
}