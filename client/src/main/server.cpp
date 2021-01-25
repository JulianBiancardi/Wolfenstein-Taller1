#include "server.h"

#include "../../../common/src/main/packets/packing.h"

Server::Server()
    : server_socket(host, port),
      reception_queue(),
      sending_queue(),
      receiving_thread(server_socket, reception_queue),
      sending_thread(server_socket, sending_queue) {
  sync_with_server(server_socket);
  receiving_thread.start();
  sending_thread.start();
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
  unsigned char size_buf[2];
  unsigned char buf[2];
  if (server_socket.receive((char*)&size_buf, 2) != 2) {
    throw SocketError("Failed to receive packet length during server sync");
  }

  size_t size = unpacku16(size_buf);
  if (size != 2) {
    throw 1;  // TODO Failed to sync with server. Received packet of size zero.
  }

  if (server_socket.receive((char*)buf, size) != size) {
    throw SocketError(
        "Failed to receive full packet during initial server sync");
  }

  unsigned char type;
  unsigned char designated_id;
  unpack(buf, "CC", &type, &designated_id);
  if (type == 1 && designated_id != 0) {
    id = designated_id;
  } else {
    throw 1;  // TODO Failed to receive id during server sync
  }
}

void Server::send(Packet& packet) { sending_queue.enqueue(packet); }

unsigned char Server::get_id() { return id; }