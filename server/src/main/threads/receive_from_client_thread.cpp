#include "receive_from_client_thread.h"

#include <syslog.h>

#include <cstddef>

#include "../../../../common/src/main/packets/packing.h"

#define END_OF_CONNECTION 0

ReceiveFromClientThread::ReceiveFromClientThread(
    Socket& connected_socket, BlockingQueue<Packet>& reception_queue)
    : connected_socket(connected_socket),
      reception_queue(reception_queue),
      allowed_to_run(true),
      running(false) {}

ReceiveFromClientThread::~ReceiveFromClientThread() {}

void ReceiveFromClientThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      unsigned char size_buf[2];
      connected_socket.receive((char*)&size_buf, 1);
      size_t size = unpacku16(size_buf);
      unsigned char* buf = new unsigned char[size];
      connected_socket.receive((char*)buf, size);
      Packet packet(size, buf);
      if (packet.get_type() == END_OF_CONNECTION) {
        allowed_to_run = false;
      }
      reception_queue.enqueue(packet);
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