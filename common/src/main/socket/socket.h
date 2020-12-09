#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <cstring>
#include <unistd.h>

#define CLIENT 0
#define SERVER 1

class Socket{
public:
    Socket();
    Socket(const Socket& copy) = delete;
    Socket& operator=(const Socket &copy) = delete;
    Socket(Socket &&other) noexcept;
    Socket& operator=(Socket &&other);
    ~Socket();

    //Acepto un cliente y devuelvo un socket por movimiento.
    Socket accept();
    //Relaciona el socket con la dirección y un puerto determinado.
    //Se escuchan las conexiones mediante el socket.
    void bind_and_listen(const char *service);

    //Permite a un cliente conectarse al servidor.
    void connect(const char *host_name, const char *service);

    //Facilita el envio de mensaje mediante el socket.
    int send(const char *buffer, size_t length) const;

    //Permite la recepción de mensaje mediante el socket.
    int receive(char *buffer, size_t buf_length) const;

    // Se hace un shutdown del canal.
    // Si kind vale 2, se cierra la escritura y lectura, sino solo escritura.
    void shutdown(int kind) const;

    //Se cierra el canal de comunicación.
    void close() const;

private:
    int fd;
    explicit Socket(int fd);

    //Facilita la modularización.
    //Además, según el tipo, se determina el hint servidor/cliente.
    void set_hints(addrinfo *hints, int kind);
};

#endif //TP3_COMMON_SOCKET_H
