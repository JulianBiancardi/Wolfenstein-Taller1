#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "client_manager.h"

class Server {
 private:
  ClientManager client_manager;

 public:
  Server();
  ~Server();

  void run_server(std::string& port);
};

#endif
