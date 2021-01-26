#ifndef CLIENT_ERROR_H
#define CLIENT_ERROR_H

#include <exception>

#define BUF_SIZE 256

class ClientError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  ClientError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~ClientError() noexcept;
};

#endif