//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H


#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/GameServerReceiver.h"
#include "../model/TowerDefenseGame.h"
#include "QueueProtected.h"
#include "ClientSender.h"
#include "../common/GameServerSocket.h"

class Server;

class Client {
public:
    Client(Socket&& socket,
           const std::vector<Communication::NameAndID> &matches,
           const std::vector<Communication::NameAndID> &maps,
           Server& server);

    void start();
    void stop();

    ~Client();

    void sendGameState(const Communication::GameState &gameState);
    void sendMessage(std::string&& msg, std::string&& nickname);
    void sendPing(Vector position);

    void setModelPlayer(const Player &player);
    void setName(const std::string& name);
    // setea al jugador como listo para empezar la partida
    void setReady();
    void setActionsQueue(QueueProtected& queue);

    const std::string& getName() const;
    const Player& getModelPlayer() const;
    // retorna si esta listo para comenzar la partida
    bool isReady() const;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client& operator=(Client&&) = delete;
    Client(Client&&) = delete ;

private:
    BlockingQueue queue;

    GameServerReceiver serverReceiver;
    GameServerSocket serverSocket;

    ClientSender sender;

    const Player* player;
    std::string name;
    bool is_ready;
};

#endif //TOWERDEFENSE_CLIENT_H
