//
// Created by facundo on 27/10/17.
//

#include "Client.h"
#include "Server.h"
#include "Actions/SendGameStateAction.h"
#include "Actions/SendMessageAction.h"
#include "Actions/DisconnectAction.h"
#include "Actions/PingAction.h"
#include "../common/Exception.h"

Client::Client(Socket&& socket, Server& server) :
        serverReceiver(server, *this),
        serverSocket(serverReceiver, std::move(socket)),
        sender(serverSocket, queue), is_ready(false) {
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

void Client::sendMessage(std::string&& msg, std::string&& nickname) {
    if (sender.isOperational()) {
        queue.push(new SendMessageAction(std::move(msg), std::move(nickname)));
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

void Client::start(const std::vector<Communication::NameAndID> &matches,
                   const std::vector<Communication::NameAndID> &maps) {
    sender.start();
    serverSocket.start();
    serverSocket.sendInitialData(matches, maps);
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

void Client::setReady() {
    is_ready = true;
}

bool Client::isReady() const {
    return is_ready;
}

void Client::sendElementUnavailable(const std::string& element,
                                    const std::string& nickname) {
    serverSocket.makeElementUnavailable(
            Communication::to_element(element), nickname);
}
