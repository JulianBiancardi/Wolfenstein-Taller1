#include "range_error.h"

#include <cstdarg>
#include <cstdio>

RangeError::RangeError(const char* format, ...) noexcept {
  va_list args;
  va_list args_copy;

  va_start(args, format);
  va_copy(args_copy, args);

  ssize_t msg_len = vsnprintf(nullptr, 0, format, args);
  error_msg.resize(msg_len);
  vsnprintf(&error_msg[0], msg_len, format, args);

  va_end(args_copy);
  va_end(args);
}

const char* RangeError::what() const noexcept { return error_msg.c_str(); }

RangeError::~RangeError() {}