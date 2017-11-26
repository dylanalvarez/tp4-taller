#define _POSIX_C_SOURCE 200112L

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <utility>
#include <iostream>
#include <vector>
#include <cstring>

#include "ServerSocket.h"
#include "AcceptFailedException.h"

ServerSocket::ServerSocket(const std::string &port) :
        wasManuallyShutDown(false) {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *result;
    int exitCode = getaddrinfo(nullptr, port.c_str(), &hints, &result);
    if (exitCode != 0) { throw Exception(gai_strerror(exitCode)); }

    for (struct addrinfo *ptr = result;
         ptr != nullptr;
         ptr = ptr->ai_next) {
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype,
                                ptr->ai_protocol);
    }

    if (fileDescriptor == -1) {
        freeaddrinfo(result);
        throw Exception("Could not connect");
    }

    if (bind(fileDescriptor, result->ai_addr, result->ai_addrlen) == -1) {
        freeaddrinfo(result);
        throw Exception(strerror(errno));
    }

    freeaddrinfo(result);

    if (listen(fileDescriptor, 1) == -1) { throw Exception(strerror(errno)); }
}

bool ServerSocket::canAccept() {
    return !wasManuallyShutDown;
}

Socket ServerSocket::accept() const {
    try {
        int client_skt = ::accept(fileDescriptor, nullptr, nullptr);
        if (client_skt == -1) throw AcceptFailedException();
        return Socket(client_skt);
    } catch (const std::runtime_error &error) {
        throw AcceptFailedException();
    }
}

void ServerSocket::shutdown() {
    ::shutdown(this->fileDescriptor, SHUT_RDWR);
    close(this->fileDescriptor);
    wasManuallyShutDown = true;
}

ServerSocket::~ServerSocket() {
    if (!wasManuallyShutDown) shutdown();
}
