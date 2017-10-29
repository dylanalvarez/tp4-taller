//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H


#include "Thread.h"
#include "../../client-server/common_Socket.h"
#include "../../estandar_de_comunicacion/GameServerSocket.h"
#include "../model/TowerDefenseGame.h"

class Server;

class Client : public Thread {
public:
    Client(Socket&& socket,
           const std::vector<Communication::NameAndID> &matches,
           const std::vector<Communication::NameAndID> &maps,
           Server& server);

    ~Client() override;

    void run() override;

    void sendGameState(const Communication::GameState &gameState);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;
    Client(Client&&) noexcept;

private:
    GameServerSocket serverSocket;
    Server& server;

    const std::vector<Communication::NameAndID> &maps;
    const std::vector<Communication::NameAndID> &matches;

    TowerDefenseGame* game;

    void performInitialTasks();
};

#endif //TOWERDEFENSE_CLIENT_H
