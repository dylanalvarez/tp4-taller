#include <iostream>
#include <syslog.h>
#include <dirent.h>
#include <cstring>
#include "src/server/Server.h"

int main(int argc, char *argv[]) {
    try{
        Server server(argv[1]);

        std::cout << "Cargando archivos...\n";

        DIR *dir;
        struct dirent *ent = nullptr;
        if ((dir = opendir ("maps/"))) {
            // itera todos los archivos en la carpeta "maps"
            while ((ent = readdir (dir))) {
                if (std::strcmp(ent->d_name, ".") != 0
                    && std::strcmp(ent->d_name, "..") != 0) {
                    server.addMap("maps/" + std::string(ent->d_name));
                }
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("");
            return EXIT_FAILURE;
        }

        std::cout << "Iniciando servidor...\n\n";

        server.start();

        std::cout << "Server up!\n";

        char input;
        do{
            std::cin >> input;
        } while (input != 'q');

        std::cout << "Server down!\n";

        server.stop();
        server.join();
    } catch (std::exception& e) {
        syslog(LOG_CRIT, "Error: %s\n", e.what());
        return -1;
    }
    return 0;
}
