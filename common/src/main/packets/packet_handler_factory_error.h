#ifndef PACKET_HANDLER_FACTORY_ERROR_H
#define PACKET_HANDLER_FACTORY_ERROR_H

#include <exception>

#define BUF_SIZE 256

class PacketHandlerFactoryError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  PacketHandlerFactoryError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~PacketHandlerFactoryError() noexcept;
};

#endif