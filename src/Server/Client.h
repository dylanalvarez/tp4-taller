//
// Created by facundo on 27/10/17.
//

#ifndef TOWERDEFENSE_CLIENT_H
#define TOWERDEFENSE_CLIENT_H


#include "Thread.h"
#include "../../client-server/common_Socket.h"
#include "../../estandar_de_comunicacion/GameServerReceiver.h"
#include "../../estandar_de_comunicacion/GameServerSocket.h"
#include "../model/TowerDefenseGame.h"

class Client : public Thread {
public:
    explicit Client(Socket&& socket, TowerDefenseGame& game);
    ~Client() override;

    void run() override;

private:
    GameServerReceiver receiver;
    TowerDefenseGame& game;
    Socket socket;
};


#endif //TOWERDEFENSE_CLIENT_H
