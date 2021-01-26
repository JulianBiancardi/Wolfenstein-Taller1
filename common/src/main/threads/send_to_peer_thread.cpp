#include "send_to_peer_thread.h"

#include <syslog.h>

#include <utility>

#include "../../../../common/src/main/packets/packing.h"

SendToPeerThread::SendToPeerThread(unsigned int client_id,
                                   Socket& connected_socket,
                                   BlockingQueue<Packet>& events_queue)
    : client_id(client_id),
      connected_socket(connected_socket),
      sending_queue(events_queue),
      allowed_to_run(true),
      running(false) {}

SendToPeerThread::~SendToPeerThread() {}

void SendToPeerThread::force_stop() {
  allowed_to_run = false;
  unsigned char data[2];

  size_t size = pack(data, "CC", END_OF_CONNECTION, client_id);
  Packet disconnection_packet(size, data);
  sending_queue.enqueue(disconnection_packet);
}

bool SendToPeerThread::is_running() { return running; }

void SendToPeerThread::run() {
  try {
    running = true;
    while (allowed_to_run) {
      Packet packet;
      sending_queue.dequeue(packet);

      size_t packet_size = packet.get_size();
      connected_socket.send(&packet_size, 2);
      connected_socket.send(packet.get_data(), packet_size);
    }
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] SendToServerThread - Unknown error");
  }
}
