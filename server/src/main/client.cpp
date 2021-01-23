#include "client.h"

#include <utility>

#include "threads/receive_from_client_thread.h"
#include "threads/send_to_client_thread.h"

Client::Client(unsigned int id, Socket& socket,
               BlockingQueue<Packet>& reception_queue)
    : id(id), sending_queue() {
  this->client_socket = std::move(socket);
  this->receiving_thread =
      new ReceiveFromClientThread(id, client_socket, reception_queue);
  this->sending_thread =
      new SendToClientThread(id, client_socket, sending_queue);

  this->receiving_thread->start();
  this->sending_thread->start();
}

Client::~Client() {
  if (receiving_thread->is_running()) {
    receiving_thread->force_stop();
    receiving_thread->join();
  }
  if (sending_thread->is_running()) {
    sending_thread->force_stop();
    sending_thread->join();
  }
}

void Client::send(Packet& packet) { sending_queue.enqueue(packet); }

bool Client::is_active() { return receiving_thread->is_running(); }