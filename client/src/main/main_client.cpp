#include <syslog.h>

#include <cstdlib>
#include <exception>
#include <iostream>  // TODO DElete

#include "client.h"
int main(int argc, char** argv) {
  try {
    Client client;
    client.run_client(argc, argv);
    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Error: %s\n", e.what());
    printf("Error: %s\n", e.what());  // TODO Delete eventually
    return EXIT_FAILURE;
  } catch (...) {
    syslog(LOG_ERR, "[Error] Server Main Thread - Unknown error\n");
    return EXIT_FAILURE;
  }
}
