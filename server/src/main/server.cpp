#include "server.h"

#include <iostream>

#include "../../../common/src/main/socket/socket.h"
#include "threads/accept_clients_thread.h"
#include "threads/processor_thread.h"

#define STOP_SERVER_CODE 'q'

Server::Server() : client_manager(), match_manager() {}

Server::~Server() {}

void Server::run_server(std::string& port) {
  Socket acceptor_socket;
  acceptor_socket.bind_and_listen(port.c_str());

  AcceptClientsThread accepting_thread(acceptor_socket, client_manager);
  accepting_thread.start();

  ProcessorThread processor_thread(client_manager);
  processor_thread.start();

  std::cout << "Successful opening the server on the port " + port << std::endl;
  std::cout << "To close the server type: " + STOP_SERVER_CODE << std::endl;
  char code;
  while (true) {
    std::cin >> code;
    if (code == STOP_SERVER_CODE) {
      accepting_thread.force_stop();
      accepting_thread.join();

      processor_thread.force_stop();
      processor_thread.join();
      break;
    }
  }
}
