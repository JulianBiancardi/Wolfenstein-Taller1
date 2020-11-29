#include <string>
#include "socket_error.h"

SocketError::SocketError(const std::string &msg) noexcept:error_msg(msg) {}

const char* SocketError::what() const noexcept{
    return error_msg.c_str();
}

SocketError::~SocketError() noexcept{}
