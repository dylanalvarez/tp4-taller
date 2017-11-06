//
// Created by facundo on 27/10/17.
//

#include <iostream>
#include "Match.h"

Match::Match(const std::string &config_file_path,
             const std::string &map_file_path, int id) :
                horde_creator(map_file_path),
                game(config_file_path, map_file_path, horde_creator.getTotalAmountOfEnemies()),
                context(game, clients), id(id)  {
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

        Horde horde = horde_creator.getNextHorde();
        for (int i = 0; i < horde.getQuantity(); i++) {
            game.addEnemy(horde.getType());
        }

        while (!actions_queue.empty()) {
            actions_queue.front().apply(context);
            actions_queue.pop();
        }

        game.updateGame();

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

TowerDefenseGame *Match::getGame() {
    return &game;
}

int Match::getID() const {
    return id;
}

void Match::addPlayer(Client* client) {
    if (has_started) { return; }

    const Player& player = game.addPlayer(client->getName(), client->getElement());
    client->setModelPlayer(player);
    client->setActionsQueue(actions_queue);
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
