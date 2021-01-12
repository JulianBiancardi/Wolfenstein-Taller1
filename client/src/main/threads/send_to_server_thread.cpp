#include "send_to_server_thread.h"

#include <utility>

SendToServerThread::SendToServerThread(Socket& connected_socket,
                                       BlockingQueue<Event>* events_queue) {
  this->connected_socket = std::move(connected_socket);
  this->events_queue = events_queue;
}

SendToServerThread::~SendToServerThread() {}

void SendToServerThread::run() {
  Event event;
  events_queue->dequeue(event);
}
