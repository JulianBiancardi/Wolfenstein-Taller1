#include "packet_handler_factory_error.h"

#include <errno.h>
#include <string.h>

#include <cstdarg>
#include <cstdio>

PacketHandlerFactoryError::PacketHandlerFactoryError(const char* format,
                                                     ...) noexcept {
  int _errno = errno;

  // Compose the message into the error_msg
  va_list args;
  va_start(args, format);
  ssize_t msg_len = vsnprintf(error_msg, BUF_SIZE, format, args);
  va_end(args);

  // Add error number description to the error message.
  strncpy(error_msg + msg_len, strerror(_errno), BUF_SIZE - msg_len);
  error_msg[BUF_SIZE - 1] = '\0';
}

const char* PacketHandlerFactoryError::what() const noexcept {
  return error_msg;
}

PacketHandlerFactoryError::~PacketHandlerFactoryError() {}
