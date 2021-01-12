#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>

#include <string>

#include "socket_error.h"

typedef unsigned long size_t;

class Socket {
 private:
  int socket_file_descriptor;
  explicit Socket(int sfd) : socket_file_descriptor(sfd) {}

 public:
  Socket();
  explicit Socket(std::string& host, std::string& port);
  Socket(Socket&& other);

  /* Send a stream using the socket.
   * Returns the amount of bytes sent.
   */
  ssize_t send(const char* stream, size_t stream_len) const;

  /* Receives a stream using the socket.
   * Returns the amount of bytes received.
   */
  ssize_t receive(char* buffer, size_t buffer_len) const;

  /* Binds it to a service and marks it as awaiting incoming connections.

   * Throws SocketError in the event of an error.
   */
  void bind_and_listen(const char* service);

  /* Accept the first connection queued in the pending connections
   * Returns a peer Socket used for the connection.
   */
  Socket accept() const;

  /* Attempts to connect the _socket to the host:service. Returns 0 on
   * success, -1 otherwise.
   */
  void connect_to(const char* host, const char* service);

  /* Shutdown all or part of the connection associated to the socket.
   * Values for mode:
   * SHUT_RD - Disables further receive operations.
   * SHUT_WR - Disables further send oeprations.
   * SHUT_RDWR - Disables further send and receive operations.
   */
  int shutdown(int how);

  /* Closes the socket.
   * Returns 0 on success, otherwise -1 shall be returned
   * and errno set to indicate the error.
   */
  int close();

  Socket& operator=(Socket&& other);

  ~Socket();
};

#endif
