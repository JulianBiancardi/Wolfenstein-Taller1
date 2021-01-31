#include <syslog.h>

#include <cstdlib>

#include "server.h"

#define PORT 1

int main(int argc, char **argv) {
  try {
    std::string port(argv[PORT]);
    Server server;
    server.run_server(port);
    return EXIT_SUCCESS;
  } catch (const std::exception &e) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Error: %s", e.what());
    printf("%s", e.what());  // TODO Delete eventually
    return EXIT_FAILURE;
  } catch (...) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Unknown error");
    return EXIT_FAILURE;
  }
}
