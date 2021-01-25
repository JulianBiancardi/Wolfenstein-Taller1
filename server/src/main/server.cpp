#include "server.h"

#include <iostream>

#include "../../../common/src/main/socket/socket.h"
#include "threads/accept_clients_thread.h"
#include "threads/processor_thread.h"

Server::Server() : client_manager() {}

Server::~Server() {}

void Server::run_server(std::string& port) {
  Socket acceptor_socket;
  acceptor_socket.bind_and_listen(port.c_str());

  AcceptClientsThread accepting_thread(acceptor_socket, client_manager);
  accepting_thread.start();

  ProcessorThread processor_thread(client_manager);
  processor_thread.start();

  char code;
  while (true) {
    std::cin >> code;
    if (code == 'q') {
      accepting_thread.force_stop();
      accepting_thread.join();

      // TODO Stop Processor Thread
      break;
    }
  }
}