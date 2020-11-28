#include "socket.h"
#include <cerrno>
#include <utility>
#include <iostream>
#include "socket_error.h"

#define INVALID_FD -1
#define SHUTDOWN_RDWR 2

Socket::Socket() : fd(INVALID_FD) {}

Socket::~Socket(){
    if (this->fd != INVALID_FD) ::close(this->fd);
    this->fd = INVALID_FD;
}

Socket::Socket(Socket &&other) noexcept: fd(other.fd){
    other.fd = INVALID_FD;
}

Socket::Socket(int fd) : fd(fd) {}

Socket Socket::accept() {
    int fd = ::accept(this->fd, nullptr, nullptr);
    if (fd == INVALID_FD)
        throw SocketError("Se ha producido un error en la función 'accept'.");
    return Socket(fd);
}
Socket &Socket::operator=(Socket &&other) {
    this->fd = other.fd;
    other.fd = INVALID_FD;
    return *this;
}

void Socket::bind_and_listen(const char *service){
    int status, val = 1;
    struct addrinfo hints, *results, *aux;
    set_hints(&hints, SERVER);
    status = getaddrinfo(nullptr, service, &hints, &results);
    if (status != 0) throw SocketError
         ("Se ha producido un error en la función 'getaddrinfo'.");
    for (aux = results; aux != nullptr; aux = aux->ai_next) {
        this->fd = ::socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        if (this->fd == INVALID_FD)
            continue;
        status = setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR,
                            &val, sizeof(val));
        if (status == INVALID_FD){
            ::close(this->fd);
            this->fd = INVALID_FD;
        }
        if (bind(this->fd, aux->ai_addr, aux->ai_addrlen) == 0){
            break;
        }
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
    if (this->fd == INVALID_FD)
        throw SocketError("Se ha producido un error en la función 'bind'.");
    freeaddrinfo(results);
    status = listen(this->fd, 10);
    if (status == INVALID_FD)
        throw SocketError("Se ha producido un error en la función 'listen'.");
}

void Socket::set_hints(addrinfo *hints, int kind){
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
    hints->ai_protocol = 0;
    if (kind == SERVER){
        hints->ai_flags = AI_PASSIVE;
    }else{
        hints->ai_flags = 0;
    }
}

void Socket::connect(const char *host_name, const char *service){
    int status;
    struct addrinfo hints, *results, *ptr;
    set_hints(&hints, CLIENT);
    status = getaddrinfo(host_name, service, &hints, &results);
    if (status != 0)
        throw SocketError("Error en el connect del socket.");

    for (ptr = results; ptr != nullptr; ptr = ptr->ai_next) {
        this->fd = ::socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (this->fd == INVALID_FD)
            continue;
        if (::connect(this->fd, ptr->ai_addr, ptr->ai_addrlen) == 0)
            break;
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
    freeaddrinfo(results);
    if (this->fd == INVALID_FD)
        throw SocketError("Se ha producido un error en la función 'connect'.");
}

int Socket::send(const char *buffer, size_t buf_length) const{
     size_t size_send = 0;
    while (size_send < buf_length){
        int aux = ::send(this->fd, &buffer[size_send],
                            buf_length - size_send,MSG_NOSIGNAL);
        if (aux < 0)
            throw SocketError("Se ha producido un error en la función 'send'.");
        size_send += aux;
    }
    return size_send;
}

int Socket::receive(char *buffer, size_t buf_length) const{
    size_t size_recv = 0;
    while (size_recv < buf_length){
        int aux = ::recv(this->fd, &buffer[size_recv],
                            buf_length - size_recv, 0);
        if (aux < 0)
            throw SocketError("Se ha producido un error en la función 'recv'.");
        else if (aux==0)
            return size_recv;
        size_recv += aux;
    }
    return size_recv;
}

void Socket::close() const{
    ::close(this->fd);
}

void Socket::shutdown(int kind) const{
    if (kind==SHUTDOWN_RDWR)
        ::shutdown(this->fd, SHUT_RDWR);
    else
        ::shutdown(this->fd, SHUT_WR);
}
