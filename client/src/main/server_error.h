#ifndef SERVER_ERROR_H
#define SERVER_ERROR_H

#include <exception>

#define BUF_SIZE 256

class ServerError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  ServerError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~ServerError() noexcept;
};

#endif