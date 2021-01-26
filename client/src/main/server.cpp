#include "server.h"

#include "../../../common/src/main/packets/packing.h"

Server::Server()
    : server_socket(host, port),
      reception_queue(),
      sending_queue(),
      receiving_thread(server_socket, reception_queue),
      sending_thread(server_socket, sending_queue) {
  receiving_thread.start();
  sending_thread.start();
  sync_with_server(server_socket);
}

Server::~Server() {
  if (receiving_thread.is_running()) {
    receiving_thread.force_stop();
    receiving_thread.join();
  }
  if (sending_thread.is_running()) {
    sending_thread.force_stop();
    sending_thread.join();
  }
}

void Server::sync_with_server(Socket& server_socket) {
  Packet packet;
  reception_queue.dequeue(packet);
  if (packet.get_type() != START_OF_CONNECTION) {
    throw 1;  // TODO Failed to establish connection
  }
  unsigned char type;
  unsigned int designated_id;
  unpack(packet.get_data(), "CI", &type, &designated_id);

  if (designated_id != 0) {
    id = designated_id;
    receiving_thread.set_id(id);
    sending_thread.set_id(id);
  } else {
    throw 1;  // TODO Failed to receive id during server sync
  }
}

BlockingQueue<Packet>& Server::get_reception_queue() { return reception_queue; }

void Server::send(Packet& packet) { sending_queue.enqueue(packet); }

unsigned int Server::get_id() { return id; }