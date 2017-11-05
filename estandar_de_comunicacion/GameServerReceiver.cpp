//
// Created by facundo on 30/10/17.
//

#include "GameServerReceiver.h"
#include "../src/server/Server.h"

GameServerReceiver::GameServerReceiver(Server &server, Client& client) :
        server(server), client(client) {}

GameServerReceiver::GameServerReceiver(GameServerReceiver&& other) noexcept :
        server(other.server),
        client(other.client) {}

void GameServerReceiver::setActionsQueue(QueueProtected &queue) {
    actions_queue = &queue;
}

void GameServerReceiver::joinToMatch(int match_id,
                                     const std::string &player_name) {
    server.joinMatch(client, match_id, true);
}

GameServerReceiver::~GameServerReceiver() = default;
