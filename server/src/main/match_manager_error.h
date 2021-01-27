#ifndef MATCH_MANAGER_ERROR_H
#define MATCH_MANAGER_ERROR_H

#include <exception>

#define BUF_SIZE 256

class MatchManagerError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  MatchManagerError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~MatchManagerError() noexcept;
};

#endif