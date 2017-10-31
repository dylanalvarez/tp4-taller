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

class Client {
public:
    Client(Socket&& socket,
           const std::vector<Communication::NameAndID> &matches,
           const std::vector<Communication::NameAndID> &maps,
           Server& server);

    ~Client();

    void sendGameState(const Communication::GameState &gameState);

    void setPlayer(const Player& player);
    void setName(std::string&& name);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;
    Client(Client&&) noexcept;

private:
    GameServerReceiver receiver;
    GameServerSocket serverSocket;
    const Player* player;
    std::string name;
};

#endif //TOWERDEFENSE_CLIENT_H
