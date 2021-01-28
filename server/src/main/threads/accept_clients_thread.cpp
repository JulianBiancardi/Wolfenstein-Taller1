#include "accept_clients_thread.h"

#include <syslog.h>

#include <utility>

AcceptClientsThread::AcceptClientsThread(Socket& acceptor_socket,
                                         ClientManager& client_manager)
    : client_manager(client_manager) {
  this->acceptor_socket = std::move(acceptor_socket);
  this->allowed_to_run = true;
}

AcceptClientsThread::~AcceptClientsThread() {}

void AcceptClientsThread::force_stop() {
  allowed_to_run = false;
  acceptor_socket.shutdown(SHUT_RDWR);
}

void AcceptClientsThread::run() {
  try {
    while (allowed_to_run) {
      Socket peer_socket = acceptor_socket.accept();
      client_manager.add_client(peer_socket);
      client_manager.clear();
    }
  } catch (const SocketError& e) {
    // Expected error when using force_stop()
    syslog(LOG_NOTICE, "[Notice] AcceptSocketsThread - SocketError: %s",
           e.what());
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] AcceptSocketsThread - Error: %s", e.what());
  } catch (...) {
    syslog(LOG_ERR, "[Error] AcceptSocketsThread - Unknown error");
  }
}