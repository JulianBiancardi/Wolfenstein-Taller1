#include "receive_from_client_thread.h"

#include <syslog.h>

#include <cstddef>
#include <memory>

#include "../../../../common/src/main/packets/packing.h"

ReceiveFromClientThread::ReceiveFromClientThread(
    unsigned int client_id, Socket& connected_socket,
    BlockingQueue<Packet>& reception_queue)
    : client_id(client_id),
      connected_socket(connected_socket),
      reception_queue(reception_queue),
      allowed_to_run(true),
      running(false) {}

ReceiveFromClientThread::~ReceiveFromClientThread() {}

bool ReceiveFromClientThread::is_running() { return running; }

void ReceiveFromClientThread::force_stop() {
  allowed_to_run = false;
  connected_socket.shutdown(SHUT_RD);
  // TODO Confirm if I need to shutdown here or what.
}

void ReceiveFromClientThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      unsigned char size_buf[2];
      if (connected_socket.receive((char*)&size_buf, 2) != 2) {
        throw SocketError("Failed to receive packet length");
      }

      size_t size = unpacku16(size_buf);
      if (size == 0) {
        syslog(LOG_WARNING,
               "[WARNING] ReceiveFromClientThread - Warning: Received packet "
               "of size zero");
        continue;
      }

      std::unique_ptr<unsigned char[]> buf(new unsigned char[size]);
      if (connected_socket.receive((char*)buf.get(), size) != size) {
        throw SocketError("Failed to receive full packet");
      }

      Packet packet(size, buf.get());

      // End connection if requested
      if (packet.get_type() == END_OF_CONNECTION) {
        unsigned char type;
        unsigned int id;
        unpack(packet.get_data(), "CI", &type, &id);
        if (id != client_id) {
          continue;
        }
        allowed_to_run = false;
      }

      reception_queue.enqueue(std::move(packet));
    }
  } catch (const SocketError& e) {
    syslog(LOG_ERR, "[ERROR] ReceiveFromServerThread - SocketError: %s",
           e.what());
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] ReceiveFromServerThread - Unknown error");
  }
}
