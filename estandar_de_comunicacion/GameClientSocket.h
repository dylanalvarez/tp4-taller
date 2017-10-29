#ifndef TP4_TALLER_GAME_CLIENT_SOCKET_H
#define TP4_TALLER_GAME_CLIENT_SOCKET_H

#include <string>
#include "CommunicationUtils.h"
#include "GameClientReceiver.h"

using Communication::GameState;
using Communication::NameAndID;
using Communication::Element;
using Communication::PositionalPower;
using Communication::TargetPower;
using Communication::Upgrade;
using Communication::Tower;

class GameClientSocket {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameClientSocket(const GameClientReceiver &receiver, int port);

    void chooseTeam(std::string &&nickname, int teamID);

    void chooseMap(std::string &&nickname, int mapID);

    void chooseElement(Element element);

    void sendChatMessage(std::string &&message);

    void pingTile(int x, int y);

    void applySpell(PositionalPower power);

    void applySpell(TargetPower power);

    void applyUpgrade(Upgrade upgrade);

    void buildTower(int x, int y, Tower::Type type);

    // After calling disconnect, this socket will be unusable
    void disconnect();

    // Will disconnect when going out of scope
    ~GameClientSocket();
};

#endif //TP4_TALLER_GAME_CLIENT_SOCKET_H
