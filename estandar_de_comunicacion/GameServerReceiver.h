#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"

class GameServerReceiver {
public:
    GameServerReceiver();

    void getChosenTeam(std::string &&nickname, int teamID);

    void getChosenMap(std::string &&nickname, int mapID);

    void getChosenElement(Communication::Element element);

    void getChatMessage(std::string &&message);

    void getPingedTile(int x, int y);

    void getSpell(Communication::PositionalPower power);

    void getSpell(Communication::TargetPower power);

    void getUpgrade(Communication::Upgrade upgrade);

    void buildTower(int x, int y, Communication::Tower::Type type);

    ~GameServerReceiver();
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
