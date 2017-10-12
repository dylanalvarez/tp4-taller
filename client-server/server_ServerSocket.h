#ifndef TP4_TALLER_SERVER_SOCKET_H
#define TP4_TALLER_SERVER_SOCKET_H


#include <string>
#include <array>
#include <vector>
#include "common_Socket.h"


// Creates a socket, binds and listens
class ServerSocket {
public:
    explicit ServerSocket(const std::string &port);

    // Checks if it's been shut down
    bool canAccept();

    // Waits for a client to try to connect, generates a Socket when that
    // happens. If it's shut down in the middle, it throws an
    // AcceptFailedException
    Socket accept() const;

    // Interrupts current accept() and makes this instance useless
    // (canAccept will return false from now on)
    void shutdown();

    ServerSocket(const ServerSocket &) = delete;

    ServerSocket &operator=(const ServerSocket &) = delete;

    ~ServerSocket();

private:
    int fileDescriptor;

    bool wasManuallyShutDown;
};


#endif //TP4_TALLER_SERVER_SOCKET_H
