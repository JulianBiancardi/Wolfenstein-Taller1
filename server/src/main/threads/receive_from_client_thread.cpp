#include "receive_from_client_thread.h"

#include <syslog.h>

#define END_OF_CONNECTION 0

ReceiveFromClientThread::ReceiveFromClientThread(
    Socket& connected_socket, BlockingQueue<packet_t>& reception_queue)
    : connected_socket(connected_socket),
      reception_queue(reception_queue),
      allowed_to_run(true),
      running(false) {}

ReceiveFromClientThread::~ReceiveFromClientThread() {}

void ReceiveFromClientThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      packet_t packet;
      connected_socket.receive((char*)&packet, sizeof(packet_t));
      reception_queue.enqueue(packet);
      if (packet.type == END_OF_CONNECTION) {
        break;
      }
    }
    running = false;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Unknown error");
  }
}

bool ReceiveFromClientThread::is_running() { return running; }

void ReceiveFromClientThread::force_stop() {
  allowed_to_run = false;
  // TODO Check if I need to shutdown here or what
}