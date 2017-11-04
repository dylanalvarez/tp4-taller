//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H


#include "Thread.h"
#include "../../client-server/common_Socket.h"
#include "../../estandar_de_comunicacion/GameServerSocket.h"
#include "../model/TowerDefenseGame.h"
#include "QueueProtected.h"
#include "ClientSender.h"

class Server;

class Client {
public:
    Client(Socket&& socket,
           const std::vector<Communication::NameAndID> &matches,
           const std::vector<Communication::NameAndID> &maps,
           Server& server);

    ~Client();

    void sendGameState(const Communication::GameState &gameState);
    void sendMessage(std::string& msg);

    void setModelPlayer(const Player &player);
    void setName(const std::string& name);
    void setActionsQueue(QueueProtected& queue);
    void addElement(const std::string& element);

    const std::string& getName() const;
    const std::string& getElement() const;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;
    Client(Client&&) noexcept ;

private:
    GameServerReceiver serverReceiver;
    GameServerSocket serverSocket;

    ClientSender sender;
    BlockingQueue queue;

    const Player* player;
    std::string name;
    std::string element;
};

#endif //TOWERDEFENSE_CLIENT_H
