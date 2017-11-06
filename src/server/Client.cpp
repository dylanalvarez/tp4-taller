//
// Created by facundo on 27/10/17.
//

#include "Client.h"
#include "Server.h"
#include "Actions/SendGameStateAction.h"
#include "Actions/SendMessageAction.h"
#include "Actions/DisconnectAction.h"
#include "Actions/PingAction.h"

Client::Client(Socket&& socket,
               const std::vector<Communication::NameAndID> &matches,
               const std::vector<Communication::NameAndID> &maps, Server& server) :
        serverReceiver(server, *this),
        serverSocket(serverReceiver, std::move(socket)),
        sender(serverSocket, queue) {
    this->element = "fire";
    this->name = "alguien";
}

Client::~Client() {
    sender.join();
    serverSocket.join();
}

void Client::sendGameState(const Communication::GameState &gameState) {
    if (sender.isOperational()) {
        queue.push(new SendGameStateAction(gameState));
    }
}

void Client::sendMessage(std::string&& msg) {
    if (sender.isOperational()) {
        queue.push(new SendMessageAction(std::move(msg), name));
    }
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

void Client::start() {
    sender.start();
    serverSocket.start();
    serverReceiver.createMatch(0, name);
}

void Client::stop() {
    sender.stop();
    serverSocket.disconnect();
    queue.push(new DisconnectAction());
}

const Player &Client::getModelPlayer() const {
    return *player;
}

void Client::sendPing(Vector position) {
    if (sender.isOperational()) {
        queue.push(new PingAction(position));
    }
}
