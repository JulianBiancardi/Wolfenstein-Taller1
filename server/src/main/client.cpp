#include "client.h"

#include <utility>

#include "threads/receive_from_client_thread.h"
#include "threads/send_to_client_thread.h"

Client::Client(int id, Socket& socket, BlockingQueue<packet_t>& reception_queue)
    : sending_queue() {
  this->client_socket = std::move(socket);
  this->receiving_thread =
      new ReceiveFromClientThread(client_socket, reception_queue);
  this->sending_thread = new SendToClientThread(client_socket, sending_queue);

  this->receiving_thread->start();
  this->sending_thread->start();
}

Client::~Client() {}

void Client::send(packet_t& packet) { sending_queue.enqueue(packet); }

bool Client::is_active() { return receiving_thread->is_running(); }