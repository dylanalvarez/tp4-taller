#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"

using Communication::GameState;
using Communication::NameAndID;
using Communication::Element;
using Communication::PositionalPower;
using Communication::TargetPower;
using Communication::Upgrade;
using Communication::Tower;

class GameServerReceiver {
public:
    GameServerReceiver();

    void getChosenTeam(std::string &&nickname, int teamID);

    void getChosenMap(std::string &&nickname, int mapID);

    void getChosenElement(Element element);

    void getChatMessage(std::string &&message);

    void getPingedTile(int x, int y);

    void getSpell(PositionalPower power);

    void getSpell(TargetPower power);

    void getUpgrade(Upgrade upgrade);

    void buildTower(int x, int y, Tower::Type type);

    ~GameServerReceiver();
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
