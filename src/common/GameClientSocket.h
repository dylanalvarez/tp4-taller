#ifndef TP4_TALLER_GAME_CLIENT_SOCKET_H
#define TP4_TALLER_GAME_CLIENT_SOCKET_H

#include <string>
#include "CommunicationUtils.h"
#include "GameClientReceiver.h"
#include "Socket.h"
#include "Thread.h"

class GameClientSocket : public Thread {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameClientSocket(GameClientReceiver &receiver, Socket&& socket);

	//falta un Start(). Para controlar en que hilo recibe.

    void chooseTeam(std::string &&nickname, int teamID);

    void chooseMap(std::string &&nickname, int mapID);

    void chooseElement(Communication::Element element);

    void sendChatMessage(std::string &&message);

    void pingTile(int x, int y);

    void applySpell(Communication::PositionalPower power);

    void applySpell(Communication::TargetPower power);

    void applyUpgrade(Communication::Upgrade upgrade);

    void buildTower(int x, int y, Communication::Tower::Type type);

    // After calling disconnect, this socket will be unusable
    void disconnect();

    // Will disconnect when going out of scope
    ~GameClientSocket();

private:
    GameClientReceiver& receiver;
    Socket socket;
};

#endif //TP4_TALLER_GAME_CLIENT_SOCKET_H
