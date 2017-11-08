#define _POSIX_C_SOURCE 200112L

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <utility>
#include <iostream>
#include <vector>
#include <cstring>

#include "Exception.h"
#include "Socket.h"


#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0 // for macOS compatibility
#endif

Socket::Socket(const std::string &ip, const std::string &port) {
    struct addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result;
    int exitCode = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
    if (exitCode != 0) throw Exception(gai_strerror(exitCode));

    bool success = false;
    for (struct addrinfo *ptr = result;
         ptr != nullptr && !success;
         ptr = ptr->ai_next) {
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype,
                                ptr->ai_protocol);
        if (fileDescriptor != -1) {
            exitCode = connect(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
            if (exitCode != -1)
                success = true;
            else
                close(fileDescriptor);
        }
    }

    freeaddrinfo(result);
    if (!success) throw Exception(strerror(errno));
}

void Socket::send(const std::vector<char> &content) const {
    size_t sentBytes = 0;
    auto sizeInBytes = content.size();
    while (sentBytes < sizeInBytes) {
        ssize_t sent = ::send(this->fileDescriptor,
                              &content[sentBytes],
                              sizeInBytes - sentBytes,
                              MSG_NOSIGNAL);
        if (sent <= 0) { throw Exception(strerror(errno)); }
        sentBytes += sent;
    }
}

void Socket::send(const std::string &content) const {
    send(std::vector<char>(content.begin(), content.end()));
}

std::vector<char> Socket::receive(size_t sizeInBytes) const {
    if (sizeInBytes == 0) { return std::vector<char>(); }
    size_t receivedBytes = 0;
    std::vector<char> buffer(sizeInBytes);
    while (receivedBytes < sizeInBytes) {
        ssize_t received = recv(this->fileDescriptor,
                                &buffer[receivedBytes],
                                sizeInBytes - receivedBytes,
                                MSG_NOSIGNAL);
        if (received < 0) {
            throw Exception(strerror(errno));
        } else if (received == 0) {
            return std::vector<char>();
        }
        receivedBytes += received;
    }
    return buffer;
}

std::string Socket::receiveString(size_t length) const {
    if (length == 0) { return std::string(); }
    std::vector<char> received = receive(length);
    return std::string(received.begin(), received.end());
}

Socket::~Socket() {
    if (fileDescriptor == -1) { return; }
    shutdown(this->fileDescriptor, SHUT_RDWR);
    close(this->fileDescriptor);
}

Socket::Socket(int fileDescriptor) :
        fileDescriptor(fileDescriptor) {}

Socket::Socket(Socket && other) noexcept {
    this->fileDescriptor = other.fileDescriptor;
    other.fileDescriptor = -1;
}

Socket &Socket::operator=(Socket && other) noexcept {
    this->fileDescriptor = other.fileDescriptor;
    other.fileDescriptor = -1;
    return *this;
}
