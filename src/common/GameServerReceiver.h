#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"
#include "../model/TowerDefenseGame.h"
#include "../../client-server/common_Socket.h"
#include "../server/QueueProtected.h"

class Server;
class Client;
class QueueProtected;

class GameServerReceiver {
public:
    GameServerReceiver(Server &server, Client& client);
    ~GameServerReceiver();

    void joinToMatch(int match_id, const std::string& player_name);

    void createMatch(int map_id, const std::string& player_name);

    void startMatch();

    void getChosenTeam(std::string &&nickname, int teamID);

    void getChosenMap(std::string &&nickname, int mapID);

    void getChosenElement(Communication::Element element);

    void getChatMessage(std::string &&message);

    void getPingedTile(int x, int y);

    void getSpell(Communication::PositionalPower power);

    void getSpell(Communication::TargetPower power);

    void getUpgrade(Communication::Upgrade upgrade);

    void buildTower(int x, int y, Communication::Tower::Type type);

    void setActionsQueue(QueueProtected& queue);

    GameServerReceiver(GameServerReceiver&&) noexcept ;
    GameServerReceiver(const GameServerReceiver&) = delete;
    GameServerReceiver& operator=(const GameServerReceiver&) = delete;

private:
    Server& server;
    Client& client;
    int my_match_id;

    QueueProtected* actions_queue;
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
