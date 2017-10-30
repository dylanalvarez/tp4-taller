//
// Created by facundo on 30/10/17.
//

#include "GameServerReceiver.h"
#include "../src/Server/Server.h"

GameServerReceiver::GameServerReceiver(Socket &socket, Server &server, Client& client) :
        socket(socket), server(server), client(client) {}

void GameServerReceiver::run() {
    // true de "estoy creando" y 0 es el id del mapa "mapa_inicial.yaml"
    server.joinToMatch(client, 0, true);
}

GameServerReceiver::GameServerReceiver(GameServerReceiver&& other) noexcept :
        socket(other.socket),
        server(other.server),
        client(other.client) {}

GameServerReceiver::~GameServerReceiver() = default;
