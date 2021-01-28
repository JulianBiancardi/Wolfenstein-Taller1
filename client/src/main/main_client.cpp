#include <syslog.h>

#include <exception>

#include "client.h"
int main(int argc, char** argv) {
  try {
    Client client;
    client.run_client(argc, argv);
    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Error: %s", e.what());
    return EXIT_FAILURE;
  } catch (...) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Unknown error");
    return EXIT_FAILURE;
  }
}
