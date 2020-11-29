#ifndef TP3_SOCKET_ERROR_H
#define TP3_SOCKET_ERROR_H

#include <typeinfo>
#include <string>

class SocketError : public std::exception {
private:
    std::string error_msg;
public:
    explicit SocketError(const std::string &msg) noexcept;
    //Devuelve el mensaje de error.
    virtual const char * what() const noexcept;
    virtual ~SocketError() noexcept;
};

#endif //TP3_SOCKET_ERROR_H
