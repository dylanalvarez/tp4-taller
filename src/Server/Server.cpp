//
// Created by facundo on 27/10/17.
//

#include "Server.h"
#include "Client.h"

Server::Server(const std::string& port) : accept_socket(port) {}

Server::~Server() = default;

void Server::run() {
    while (accept_socket.canAccept()) {
        Socket new_client = accept_socket.accept();

        if (accept_socket.canAccept()) {
            // se pudo cerrar el socket en el accept

            /*** mandar mapas disponibles para crear
               y partidas disponibles para unirse ***/

            /*** una vez recibida la partida a unirse o el mapa a crear
                 se crea el cliente y se lo agrega al match correspondiente ***/

            /**Client client(std::move(new_client), game);*/
        }
    }
}

void Server::stop() {
    accept_socket.shutdown();
}
