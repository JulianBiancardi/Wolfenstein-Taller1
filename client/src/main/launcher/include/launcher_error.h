#ifndef LAUNCHER_ERROR_H
#define LAUNCHER_ERROR_H

#include <exception>

#define BUF_SIZE 256

class LauncherError : public std::exception {
 private:
  char error_msg[BUF_SIZE];

 public:
  LauncherError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~LauncherError() noexcept;
};

#endif