#ifndef RANGE_ERROR_H
#define RANGE_ERROR_H

#include <exception>
#include <string>

class RangeError : public std::exception {
 private:
  std::string error_msg;

 public:
  RangeError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~RangeError() noexcept;
};

#endif
