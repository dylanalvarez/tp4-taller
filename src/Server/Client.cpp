//
// Created by facundo on 27/10/17.
//

#include "Client.h"
#include "Server.h"

Client::Client(Socket&& socket,
               const std::vector<Communication::NameAndID> &matches,
               const std::vector<Communication::NameAndID> &maps, Server& server) :
        serverSocket(std::move(socket)),
        server(server), maps(maps), matches(matches) {}

Client::~Client() = default;

void Client::run() {
    performInitialTasks();
    /** recibir opcodes de hechizos, construccion de torres, mensajes y ping */
}

void Client::performInitialTasks() {
    serverSocket.sendInitialData(matches, maps);
    int id = serverSocket.getChosen();
    game = server.joinToMatch(*this, id, serverSocket.isCreating()).getGame();

    game->addPlayer(serverSocket.getNickName(), serverSocket.getElement());
}

void Client::sendGameState(const Communication::GameState &gameState) {
    serverSocket.sendGameState(gameState);
}

Client::Client(Client&& other) noexcept :
        serverSocket(std::move(other.serverSocket)),
        server(other.server),
        maps(other.maps),
        matches(matches) {
    this->game = other.game;
    other.game = nullptr;
}
