#ifndef TP4_TALLER_GAME_SERVER_RECEIVER_H
#define TP4_TALLER_GAME_SERVER_RECEIVER_H

#include <string>
#include "CommunicationUtils.h"

class GameServerReceiver {
public:
    GameServerReceiver();

    void chooseTeam(std::string &&nickname, int teamID);

    void chooseMap(std::string &&nickname, int mapID);

    void chooseElement(Element element);

    void sendChatMessage(std::string &&message);

    void pingTile(int x, int y);

    void applySpell(PositionalPower power);

    void applySpell(TargetPower power);

    void applyUpgrade(Upgrade upgrade);

    void buildTower(int x, int y, Tower::Type type);

    ~GameServerReceiver();
};

#endif //TP4_TALLER_GAME_SERVER_RECEIVER_H
