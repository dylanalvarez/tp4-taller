#include <vector>
#include <iostream>
#include "common_Socket.h"

int main(int argc, char *argv[]) {
    Socket socket("127.0.0.1", "8080");

    std::cout << socket.receiveString(7) << std::endl;
    socket.send("response");
}
