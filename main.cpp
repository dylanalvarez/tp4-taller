#include <iostream>
#include <syslog.h>
#include "src/server/Server.h"

int main(int argc, char *argv[]) {
    try{
        Server server(argv[1]);

        std::cout << "Ingrese las rutas de los mapas,"
                " que estaran disponibles para seleccionar.\n"
                "Presione r para terminar\n";

        std::string path;
        getline(std::cin, path);
        while (path[0] != 'r') {
            server.addMap(path);
            getline(std::cin, path);
        }

        std::cout << "Servidor iniciado\n";
        server.start();

        char input;
        do{
            std::cin >> input;
        } while (input != 'q');

        server.stop();
        server.join();
    } catch (std::exception& e) {
        syslog(LOG_CRIT, "Error: %s\n", e.what());
        return -1;
    }
    return 0;
}
