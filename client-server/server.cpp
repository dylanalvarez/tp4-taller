#include "server_ServerSocket.h"
#include <iostream>

int main(int argc, char *argv[]) {
    ServerSocket serverSocket("8080");
    Socket socket = serverSocket.accept();

    socket.send("request");
    std::cout << socket.receiveString(8) << std::endl;
}
