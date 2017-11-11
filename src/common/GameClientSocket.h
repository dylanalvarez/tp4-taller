#ifndef TP4_TALLER_GAME_CLIENT_SOCKET_H
#define TP4_TALLER_GAME_CLIENT_SOCKET_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "GameClientReceiver.h"
#include "Socket.h"
#include "Thread.h"

class GameClientSocket : public Thread {
public:
    // When it recieves a message, it will invoke a method in the receiver.
    GameClientSocket(GameClientReceiver &receiver, Socket &&socket);

    void run() override;

    void chooseTeam(std::string &&nickname, int teamID);

    void chooseMap(std::string &&nickname, std::string &&mapName, int mapID);

    void chooseElement(Communication::Element element);

    void startGame();

    void sendChatMessage(std::string &&message);

    void pingTile(int x, int y);

    void applySpell(Communication::PositionalPower power);

    void applySpell(Communication::TargetPower power);

    void applyUpgrade(Communication::Upgrade upgrade);

    void buildTower(int x, int y, Communication::Tower::Type type);

    // After calling disconnect, this socket will be unusable
    void disconnect();

    // Will disconnect when going out of scope
    ~GameClientSocket() override;

    GameClientSocket(const GameClientSocket &) = delete;

    GameClientSocket &operator=(const GameClientSocket &) = delete;

    GameClientSocket(GameClientSocket &&) noexcept;


private:
    void _sendNode(YAML::Node &node);

    void _handleInitialData(YAML::Node &node);

    void _handleGameState(YAML::Node &node);

    void _handleRecievedMessage(YAML::Node &node);

    void _handleUnavailableElement(YAML::Node &node);

    void _handlePing(YAML::Node &node);

    GameClientReceiver &receiver;
    Socket socket;
    bool keepRunning;
};

#endif //TP4_TALLER_GAME_CLIENT_SOCKET_H
