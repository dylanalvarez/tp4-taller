#ifndef TP4_TALLER_SOCKET_H
#define TP4_TALLER_SOCKET_H

#include <string>
#include <array>
#include <vector>

class Socket {
public:
    Socket(const std::string &ip, const std::string &port);

    void send(const std::vector<char> &content) const;

    void send(const std::string &content) const;

    // If the other party disconnected, it will return an empty vector
    std::vector<char> receive(size_t sizeInBytes) const;

    // If the other party disconnected, it will return an empty string
    std::string receiveString(size_t length) const;

    Socket &operator=(const Socket &) = delete;

    ~Socket();

    explicit Socket(int fileDescriptor);

private:
    int fileDescriptor;
};

#endif //TP4_TALLER_SOCKET_H
