//
// Created by facundo on 27/10/17.
//

#include "Match.h"

Match::Match(const std::string &config_file_path,
             const std::string &map_file_path, int id) :
                game(config_file_path, map_file_path), id(id) {
    game.addEnemy("abmonible");
}

Match::~Match() = default;

void Match::run() {
    while(!game.isGameOver()) {
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

Match::Match(Match&& other) noexcept : game(std::move(other.game)),
                              time_step(other.time_step) {
    this->id = other.id;
    other.id = -1;
}

void Match::addPlayer(Client &&client) {
    std::lock_guard<std::mutex> lock(mutex);
    clients.push_back(std::move(client));
}
