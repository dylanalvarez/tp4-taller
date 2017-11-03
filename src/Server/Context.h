//
// Created by facundo on 03/11/17.
//

#ifndef TOWERDEFENSE_CONTEXT_H
#define TOWERDEFENSE_CONTEXT_H

#include "../../estandar_de_comunicacion/GameServerSocket.h"

class GameServerSocket;
class Client;

class Context {
public:
    explicit Context(GameServerSocket& socket);
    explicit Context(TowerDefenseGame& game);
    explicit Context(std::vector<Client>& clients);
    Context(TowerDefenseGame& game, std::vector<Client>& clients);

    GameServerSocket& getSocket();
    TowerDefenseGame& getGame();
    std::vector<Client>& getClients();

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) noexcept ;
    Context& operator=(Context&&) noexcept ;

private:
    GameServerSocket* socket;
    TowerDefenseGame* game;
    std::vector<Client>* clients;
};


#endif //TOWERDEFENSE_CONTEXT_H
