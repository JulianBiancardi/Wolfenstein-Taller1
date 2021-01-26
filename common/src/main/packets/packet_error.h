#ifndef PACKET_ERROR_H
#define PACKET_ERROR_H

#include <exception>

#define BUF_SIZE 256

class PacketError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  PacketError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~PacketError() noexcept;
};

#endif