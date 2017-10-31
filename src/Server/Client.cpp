//
// Created by facundo on 27/10/17.
//

#include "Client.h"
#include "Server.h"

Client::Client(Socket&& socket,
               const std::vector<Communication::NameAndID> &matches,
               const std::vector<Communication::NameAndID> &maps, Server& server) :
        receiver(server, *this), serverSocket(receiver, std::move(socket)) {
    //serverSocket.sendInitialData(matches, maps);
}

Client::~Client() = default;

void Client::sendGameState(const Communication::GameState &gameState) {
    serverSocket.sendGameState(gameState);
}

Client::Client(Client&& other) noexcept : receiver(std::move(other.receiver)),
                                          serverSocket(std::move(other.serverSocket)) {
    this->player = other.player;
    other.player = nullptr;
}

void Client::setModelPlayer(const Player &player) {
    this->player = &player;
}

void Client::setName(std::string&& name) {
    this->name = std::move(name);
}

const std::string &Client::getName() const {
    return name;
}

const std::string &Client::getElement() const {
    return element;
}

void Client::addElement(std::string &&element) {
    this->element = std::move(element);
}

void Client::sendMessage(std::string& msg) {
    serverSocket.sendChatMessage(std::move(msg), std::move(name));
}

void Client::setActionsQueue(QueueProtected &queue) {
    receiver.setActionsQueue(queue);
}
