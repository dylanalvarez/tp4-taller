//
// Created by facundo on 27/10/17.
//

#include "Match.h"

Match::Match(const std::string &config_file_path,
             const std::string &map_file_path, int id) :
                horde_creator(config_file_path),
                game(config_file_path, map_file_path, horde_creator.getTotalAmountOfEnemies()),
                id(id) {
    has_started = false;
}

Match::~Match() = default;

void Match::run() {
    has_started = true;
    horde_creator.start();

    while(!game.isGameOver()) {
        Horde horde = horde_creator.getNextHorde();
        for (int i = 0; i < horde.getQuantity(); i++) {
            game.addEnemy(horde.getType());
        }

        while (!actions_queue.empty()) {
            actions_queue.front().apply(game);
            actions_queue.front().apply(clients);
            actions_queue.pop();
        }

        game.updateGame();

        /** enviar el estado del juego */
        Communication::GameState gameState = game.getGameState();
        for (Client& client : clients) {
            client.sendGameState(gameState);
        }

        usleep(time_step);
    }
}

TowerDefenseGame *Match::getGame() {
    return &game;
}

int Match::getID() const {
    return id;
}

Match::Match(Match&& other) noexcept : horde_creator(std::move(other.horde_creator)),
                                       game(std::move(other.game)),
                                       time_step(other.time_step){
    this->id = other.id;
    other.id = -1;
}

void Match::addPlayer(Client &&client) {
    if (has_started) { return; }

    const Player& player = game.addPlayer(client.getName(), client.getElement());
    client.setModelPlayer(player);
    client.setActionsQueue(actions_queue);
    clients.push_back(std::move(client));
}
