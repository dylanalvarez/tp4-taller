//
// Created by facundo on 27/10/17.
//

#include "Client.h"
#include "Server.h"
#include "Actions/SendGameStateAction.h"
#include "Actions/SendMessageAction.h"

Client::Client(Socket&& socket,
               const std::vector<Communication::NameAndID> &matches,
               const std::vector<Communication::NameAndID> &maps, Server& server) :
        serverReceiver(server, *this),
        serverSocket(serverReceiver, std::move(socket)),
        sender(serverSocket, queue) {
    this->element = "fire";
    this->name = "alguien";
    serverReceiver.joinToMatch(0, this->name);
    sender.start();
}

Client::~Client() = default;

void Client::sendGameState(const Communication::GameState &gameState) {
    queue.push(new SendGameStateAction(gameState));
}

void Client::sendMessage(std::string& msg) {
   queue.push(new SendMessageAction(msg, name));
}

void Client::setActionsQueue(QueueProtected &queue) {
    serverReceiver.setActionsQueue(queue);
}

void Client::setModelPlayer(const Player &player) {
    this->player = &player;
}

void Client::setName(const std::string& name) {
    this->name = name;
}

const std::string &Client::getName() const {
    return name;
}

const std::string &Client::getElement() const {
    return element;
}

void Client::addElement(const std::string& element) {
    this->element = element;
}

Client::Client(Client&& other) noexcept : serverReceiver(std::move(other.serverReceiver)),
                                 serverSocket(std::move(other.serverSocket)),
                                 sender(std::move(other.sender)),
                                 queue(std::move(other.queue)),
                                 player(other.player),
                                 name(std::move(other.name)),
                                 element(std::move(other.element)) {
    other.player = nullptr;
}
