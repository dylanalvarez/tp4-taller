//
// Created by facundo on 27/10/17.
//

#include <sys/socket.h>
#include "Client.h"
#include "Server.h"

Client::Client(Socket&& socket,
               const std::vector<Communication::NameAndID> &matches,
               const std::vector<Communication::NameAndID> &maps, Server& server) :
        receiver(socket, server, *this), serverSocket(receiver, std::move(socket)) {
    //serverSocket.sendInitialData(matches, maps);
}

Client::~Client() = default;

void Client::sendGameState(const Communication::GameState &gameState) {
    serverSocket.sendGameState(gameState);
}

Client::Client(Client&& other) noexcept : receiver(std::move(other.receiver)),
                                          serverSocket(std::move(other.serverSocket)) {}
