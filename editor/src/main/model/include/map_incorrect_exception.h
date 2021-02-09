#ifndef __MAP_INCORRECT_EXCEPTION_H__
#define __MAP_INCORRECT_EXCEPTION_H__

#include <stdexcept>
#include <string>

//-----------------------------------------------------------------------------

class MapIncorrectException : public std::runtime_error {
 public:
  explicit MapIncorrectException(const std::string& msg_error) noexcept
      : runtime_error(msg_error) {}
};

//-----------------------------------------------------------------------------
#endif  // __MAP_INCORRECT_EXCEPTION_H__