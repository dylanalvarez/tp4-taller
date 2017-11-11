//
// Created by facundo on 27/10/17.
//

#include <iostream>
#include "Match.h"

Match::Match(const std::string &config_file_path,
             const std::string &map_file_path, int id) :
            horde_creator(map_file_path, actions_queue),
            game(config_file_path, map_file_path, horde_creator.getTotalAmountOfEnemies()),
            context(game, clients), id(id), map(map_file_path)  {
    has_started = false;
    keep_running = true;
}

Match::~Match() {
    for (Client* client : clients) {
        delete client;
    }
}

void Match::run() {
    has_started = true;
    horde_creator.start();

    while(!game.isGameOver() && keep_running) {
        time_t start_time;
        time(&start_time);

        horde_creator.addNextEnemy();

        game.updateGame();

        while (!actions_queue.empty()) {
            actions_queue.front().apply(context);
            actions_queue.pop();
        }

        /** enviar el estado del juego */
        Communication::GameState gameState = game.getGameState();
        for (Client* client : clients) {
            client->sendGameState(gameState);
        }

        time_t end_time;
        time(&end_time);

        double time_to_sleep = time_step - (difftime(start_time, end_time) / 1000);

        if (time_to_sleep >= 0) {
           usleep((unsigned int)time_to_sleep);
        }
    }
}

int Match::getID() const {
    return id;
}

void Match::addPlayer(Client* client) {
    if (has_started) { return; }

    const Player& player = game.addPlayer(client->getName());
    client->setModelPlayer(player);
    client->setActionsQueue(actions_queue);
    client->sendMap(map);
    clients.push_back(client);
}

void Match::stop() {
    keep_running = false;
    for (Client* client : clients) {
        client->stop();
    }
}

bool Match::hasStarted() const {
    return has_started;
}

void Match::startGame() {
    for (Client* client : clients) {
        // hasta que no esten todos listos, no se inicia la partida
        if (!client->isReady()) { return; }
    }

    Thread::start();
}

void Match::addElementToClient(const Client& client_to_add,
                               const std::string& element) {
    if (hasStarted()) { return; }

    for (Client* client : clients) {
        if (&client_to_add == client) {
            try {
                game.addElementToPlayer(client->getModelPlayer(), element);
            } catch (std::exception& e) {
                client->sendElementUnavailable(element, client->getName());
            }
        } else {
            client->sendElementUnavailable(element, client->getName());
        }
    }
}
