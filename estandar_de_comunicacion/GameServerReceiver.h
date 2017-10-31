#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"
#include "../src/model/TowerDefenseGame.h"
#include "../src/Server/Thread.h"
#include "../client-server/common_Socket.h"

class Server;
class Client;

class GameServerReceiver {
public:
    GameServerReceiver(Server &server, Client& client);
    ~GameServerReceiver();

    void joinToMatch(int match_id, const std::string& player_name);

    void createMatch(int map_id, const std::string& player_name);

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
    GameServerReceiver(const GameServerReceiver&) = delete;
    GameServerReceiver& operator=(const GameServerReceiver&) = delete;

private:
    Server& server;
    Client& client;
    TowerDefenseGame* game; // o cola bloqueante
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
