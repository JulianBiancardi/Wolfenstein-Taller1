#ifndef MATCH_ERROR_H
#define MATCH_ERROR_H

#include <exception>

#define BUF_SIZE 256

class MatchError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  MatchError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~MatchError() noexcept;
};

#endif