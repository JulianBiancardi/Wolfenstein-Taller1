#include "accept_clients_thread.h"

#include <syslog.h>

#include <utility>

#include "receive_from_client_thread.h"
#include "send_to_client_thread.h"
#include "thread_set.h"

AcceptClientsThread::AcceptClientsThread(
    Socket& acceptor_socket, BlockingQueue<packet_t>* reception_queue) {
  this->acceptor_socket = std::move(acceptor_socket);
  this->allowed_to_run = true;
  this->reception_queue = reception_queue;
}

AcceptClientsThread::~AcceptClientsThread() {}

void AcceptClientsThread::force_stop() {
  allowed_to_run = false;
  acceptor_socket.shutdown(SHUT_RDWR);
}

void AcceptClientsThread::run() {
  try {
    ThreadSet threads;

    while (allowed_to_run) {
      Socket peer_socket = acceptor_socket.accept();
      ReceiveFromClientThread* recv_thread =
          new ReceiveFromClientThread(peer_socket, reception_queue);
      threads.insert(recv_thread);
      recv_thread->start();

      threads.clear();
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