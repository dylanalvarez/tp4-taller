#include <iostream>
#include "src/Server/Server.h"

int main(int argc, char *argv[]) {
    Server server("8080");

    server.start();

    char input;
    do{
        std::cin >> input;
    } while (input != 'q');

    server.stop();
    server.join();
}
