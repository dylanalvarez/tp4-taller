#include <iostream>
#include "src/Server/Server.h"

int main(int argc, char *argv[]) {
    Server server("8080");

    std::cout << "Ingrese las rutas de los mapas,"
            " que estaran disponibles para seleccionar.\n"
            "Presione r para terminar\n";

    std::string path;
    getline(std::cin, path);
    while (path[0] != 'r') {
        server.addMap(path);
        getline(std::cin, path);
    }

    std::cout << "Server iniciado...\n";
    server.start();

    char input;
    do{
        std::cin >> input;
    } while (input != 'q');

    server.stop();
    server.join();
}
