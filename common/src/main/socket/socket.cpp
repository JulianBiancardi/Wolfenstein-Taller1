#include "socket.h"

#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define ERROR -1
#define NO_ERROR 0
#define WAITING_QUEUE_MAX_LEN 5

int static get_socket_file_descriptor(
    const char* host, const char* service,
    int (*func)(int socket_file_descriptor,
                const struct sockaddr* socket_address,
                socklen_t socket_address_len));

Socket::Socket() {}
Socket::Socket(std::string& host, std::string& port) {
  connect_to(host.c_str(), port.c_str());
}
Socket::Socket(Socket&& other) {
  this->socket_file_descriptor = other.socket_file_descriptor;
  other.socket_file_descriptor = -1;
}

ssize_t Socket::send(const char* stream, size_t stream_len) const {
  ssize_t tot_bytes_sent = 0;
  while (tot_bytes_sent != (ssize_t)stream_len) {
    ssize_t bytes_sent = ::send(socket_file_descriptor, &stream[tot_bytes_sent],
                                stream_len - tot_bytes_sent, MSG_NOSIGNAL);
    if (bytes_sent == ERROR) {
      break;
    }
    tot_bytes_sent += bytes_sent;
  }
  return tot_bytes_sent;
}

ssize_t Socket::receive(char* buffer, size_t buffer_len) const {
  ssize_t tot_bytes_read = 0;
  while (tot_bytes_read != (ssize_t)buffer_len) {
    ssize_t bytes_read = recv(socket_file_descriptor, &buffer[tot_bytes_read],
                              buffer_len - tot_bytes_read, 0);
    if (bytes_read <= 0) {
      break;
    }
    tot_bytes_read += bytes_read;
  }
  return tot_bytes_read;
}

void Socket::bind_and_listen(const char* service) {
  int sfd = get_socket_file_descriptor(0, service, bind);
  if (sfd == ERROR) {
    throw SocketError("Failed to bind");
  }

  if (listen(sfd, WAITING_QUEUE_MAX_LEN) == ERROR) {
    throw SocketError("Failed to listen");
  }

  socket_file_descriptor = sfd;
}

Socket Socket::accept() const {
  int peer_file_descriptor = ::accept(socket_file_descriptor, NULL, NULL);
  if (peer_file_descriptor == ERROR) {
    throw SocketError("Failed to accept a connection");
  }

  Socket peer_socket(peer_file_descriptor);
  return peer_socket;
}

void Socket::connect_to(const char* host, const char* service) {
  int sfd = get_socket_file_descriptor(host, service, connect);
  if (sfd == ERROR) {
    throw SocketError("Failed to connect");
  }

  socket_file_descriptor = sfd;
}

int Socket::shutdown(int how) {
  return ::shutdown(socket_file_descriptor, how);
}

int Socket::close() {
  int result = ::close(socket_file_descriptor);
  if (result != ERROR) {
    socket_file_descriptor = -1;  // -1 for null socket
  }
  return result;
}

void Socket::operator()(std::string& str) { send(str.c_str(), str.length()); }

Socket::~Socket() {
  ::shutdown(socket_file_descriptor, SHUT_RDWR);
  if (socket_file_descriptor != -1) {
    ::close(socket_file_descriptor);
  }
}

Socket& Socket::operator=(Socket&& other) {
  if (this == &other) {
    return *this;
  }
  socket_file_descriptor = other.socket_file_descriptor;
  other.socket_file_descriptor = -1;

  return *this;
}

/* Given a server-host and a pointer to either the function bind or connect,
 * returns the file descriptor of a socket which has been binded or connected to
 * an obtained address. In case of failure, it returns -1.
 */
int static get_socket_file_descriptor(
    const char* host, const char* service,
    int (*func)(int socket_file_descriptor,
                const struct sockaddr* socket_address,
                socklen_t socket_address_len)) {
  int sfd;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  struct addrinfo* results;
  int status = getaddrinfo(host, service, &hints, &results);
  if (status != 0) {
    return ERROR;
  }

  struct addrinfo* rp;
  for (rp = results; rp != NULL; rp = rp->ai_next) {
    int domain = rp->ai_family;
    int type = rp->ai_socktype;
    int protocol = rp->ai_protocol;
    sfd = socket(domain, type, protocol);

    if (sfd == ERROR) {
      continue;
    }

    bool reuseable = true;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuseable, sizeof(reuseable));

    struct sockaddr* socket_address = rp->ai_addr;
    socklen_t socket_address_len = rp->ai_addrlen;
    if (func(sfd, socket_address, socket_address_len) == NO_ERROR) {
      break;
    }

    close(sfd);
  }

  freeaddrinfo(results);

  if (rp == NULL) {
    return ERROR;
  }

  return sfd;
}
