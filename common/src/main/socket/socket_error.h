#ifndef SOCKET_ERROR_H
#define SOCKET_ERROR_H

#include <exception>

#define BUF_SIZE 256

class SocketError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  SocketError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~SocketError() noexcept;
};

#endif
