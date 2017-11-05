//
// Created by facundo on 03/11/17.
//

#include "Context.h"

Context::Context(GameServerSocket &socket) : socket(&socket) {}

Context::Context(TowerDefenseGame &game) : game(&game) {}

Context::Context(std::vector<Client*> &clients) : clients(&clients){}

Context::Context(TowerDefenseGame &game, std::vector<Client*> &clients) :
        game(&game), clients(&clients){}

GameServerSocket& Context::getSocket() {
    return *socket;
}

TowerDefenseGame &Context::getGame() {
    return *game;
}

std::vector<Client*>& Context::getClients() {
    return *clients;
}

Context::Context(Context&& other) noexcept {
    this->socket = other.socket;
    this->game = other.game;
    this->clients = other.clients;

    other.socket = nullptr;
    other.game = nullptr;
    other.clients = nullptr;
}

Context &Context::operator=(Context&& other) noexcept {
    this->socket = other.socket;
    this->game = other.game;
    this->clients = other.clients;

    other.socket = nullptr;
    other.game = nullptr;
    other.clients = nullptr;

    return *this;
}
