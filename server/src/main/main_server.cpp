#include <syslog.h>

#include <cstdlib>
#include <iostream>

#include "../../../common/src/main/config_loader.h"
#include "server.h"
#define PORT 1

int main(int argc, char **argv) {
  try {
    Server server;
    std::cout << "Running server on " + CL::sv_port + " ..." << std::endl;
    server.run_server(CL::sv_port);
    return EXIT_SUCCESS;
  } catch (const std::exception &e) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Error: %s\n", e.what());
    return EXIT_FAILURE;
  } catch (...) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Unknown error\n");
    return EXIT_FAILURE;
  }
}
