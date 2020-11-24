#ifndef SDL_ERROR_H
#define SDL_ERROR_H

#include <exception>
#include <string>

class SDLError : public std::exception {
 private:
  std::string error_msg;

 public:
  SDLError(const char* format, ...) noexcept;

  /* Returns the message error */
  virtual const char* what() const noexcept;

  virtual ~SDLError() noexcept;
};

#endif
