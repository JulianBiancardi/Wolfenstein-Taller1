#include "client.h"

#include <utility>

#include "../../../../common/src/main/packets/packing.h"

Client::Client(unsigned int id, Socket& socket,
               BlockingQueue<Packet>& reception_queue)
    : id(id),
      client_socket(std::move(socket)),
      sending_queue(),
      receiving_thread(id, client_socket, reception_queue),
      sending_thread(id, client_socket, sending_queue) {
  receiving_thread.start();
  sending_thread.start();
  sync();
}

Client::~Client() {
  if (receiving_thread.is_running()) {
    receiving_thread.force_stop();
    receiving_thread.join();
  }
  if (sending_thread.is_running()) {
    sending_thread.force_stop();
    sending_thread.join();
  }
}

void Client::sync() {
  unsigned char data[START_OF_CONNECTION_SIZE];
  size_t size = pack(data, "CI", START_OF_CONNECTION, id);
  Packet connection_packet(size, data);
  sending_queue.enqueue(connection_packet);
}

void Client::send(Packet& packet) { sending_queue.enqueue(packet); }

bool Client::is_active() { return receiving_thread.is_active(); }