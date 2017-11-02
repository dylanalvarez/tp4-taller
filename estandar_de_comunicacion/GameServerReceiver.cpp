//
// Created by facundo on 30/10/17.
//

#include "GameServerReceiver.h"
#include "../src/Server/Server.h"

GameServerReceiver::GameServerReceiver(Server &server, Client& client) :
        server(server), client(client) {}

GameServerReceiver::GameServerReceiver(GameServerReceiver&& other) noexcept :
        server(other.server),
        client(other.client) {}

void GameServerReceiver::setActionsQueue(QueueProtected &queue) {
    actions_queue = &queue;
}

GameServerReceiver::~GameServerReceiver() = default;
