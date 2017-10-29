#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"
#include "../src/model/TowerDefenseGame.h"

class Server;

class GameServerReceiver : public Thread {
public:
    GameServerReceiver(Socket& socket, Server& server);
    ~GameServerReceiver() override;

    void run() override;

    void getChosenTeam(std::string &&nickname, int teamID);

    void getChosenMap(std::string &&nickname, int mapID);

    void getChosenElement(Communication::Element element);

    void getChatMessage(std::string &&message);

    void getPingedTile(int x, int y);

    void getSpell(Communication::PositionalPower power);

    void getSpell(Communication::TargetPower power);

    void getUpgrade(Communication::Upgrade upgrade);

    void buildTower(int x, int y, Communication::Tower::Type type);

    GameServerReceiver(GameServerReceiver&&) noexcept ;

private:
    Socket& socket;
    Server& server;
    TowerDefenseGame* game; // o cola bloqueante
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
