#include <yaml-cpp/yaml.h>
#include "Socket.h"
#include "GameClientSocket.h"
#include "Exception.h"

GameClientSocket::GameClientSocket(GameClientReceiver &receiver,
                                   Socket &&socket)
        : receiver(receiver), socket(std::move(socket)), keepRunning(true) {}

void GameClientSocket::run() {
    while (keepRunning) {
        try {
            std::string str_opcode = socket.receiveString(OPCODE_CHARACTER_COUNT);
            if (str_opcode.empty()) { break; }
            int opcode = std::stoi(str_opcode);
            unsigned long messageLength = std::stoul(
                    socket.receiveString(MESSAGE_LENGTH_CHARACTER_COUNT));
            std::string messageAsString = socket.receiveString(messageLength);
            YAML::Node message;
            switch (opcode) {
                case 0:
                    message = YAML::Load(messageAsString);
                    _handleInitialData(message);
                    break;
                case 2:
                    receiver.getMap(std::move(messageAsString));
                    break;
                case 3:
                    message = YAML::Load(messageAsString);
                    _handleGameState(message);
                    break;
                case 4:
                    message = YAML::Load(messageAsString);
                    _handleRecievedMessage(message);
                    break;
                case 5:
                    message = YAML::Load(messageAsString);
                    _handlePing(message);
                    break;
                case 6:
                    message = YAML::Load(messageAsString);
                    _handleUnavailableElement(message);
                    break;
                default:
                    break;
            }
        } catch (Exception& e) { return; }
    }
}

void GameClientSocket::disconnect() {
    keepRunning = false;
    socket.shutdown();
}

void GameClientSocket::_sendNode(YAML::Node& node) {
    YAML::Emitter emitter;
    emitter << node;
    std::string message(emitter.c_str());
    socket.send(Communication::toFixedLengthString(
            message.length(), MESSAGE_LENGTH_CHARACTER_COUNT));
    socket.send(message);
}

void GameClientSocket::chooseTeam(std::string &&nickname, int teamID) {
    YAML::Node node;
    node["nickname"] = nickname;
    node["id"] = teamID;
    socket.send(Communication::toFixedLengthString(
            0, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::chooseMap(std::string &&nickname,
                                 std::string &&mapName,
                                 int mapID) {
    YAML::Node node;
    node["nickname"] = nickname;
    node["map_name"] = mapName;
    node["id"] = mapID;
    socket.send(Communication::toFixedLengthString(
            1, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::chooseElement(Communication::Element element) {
    YAML::Node node;
    node["type"] = Communication::to_string(element);
    socket.send(Communication::toFixedLengthString(
            2, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::startGame() {
    socket.send(Communication::toFixedLengthString(
            3, OPCODE_CHARACTER_COUNT));
    socket.send(Communication::toFixedLengthString(
            0, MESSAGE_LENGTH_CHARACTER_COUNT));
}

void GameClientSocket::sendChatMessage(std::string &&chatMessage) {
    YAML::Node node;
    node["message"] = chatMessage;
    socket.send(Communication::toFixedLengthString(
            4, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::pingTile(int x, int y) {
    YAML::Node node;
    node["x"] = x;
    node["y"] = y;
    socket.send(Communication::toFixedLengthString(
            5, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::applySpell(Communication::PositionalPower power) {
    YAML::Node node;
    node["position"]["x"] = power.x;
    node["position"]["y"] = power.y;
    node["type"] = Communication::PositionalPower::to_string(power.type);
    socket.send(Communication::toFixedLengthString(
            6, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::applySpell(Communication::TargetPower power) {
    YAML::Node node;
    node["enemy_id"] = power.enemyID;
    node["type"] = Communication::TargetPower::to_string(power.type);
    socket.send(Communication::toFixedLengthString(
            6, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::applyUpgrade(Communication::Upgrade upgrade) {
    YAML::Node node;
    node["tower_id"] = upgrade.towerID;
    node["type"] = Communication::Upgrade::to_string(upgrade.type);
    socket.send(Communication::toFixedLengthString(
            7, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void
GameClientSocket::buildTower(int x, int y, Communication::Tower::Type type) {
    YAML::Node node;
    node["position"]["x"] = x;
    node["position"]["y"] = y;
    node["type"] = Communication::Tower::to_string(type);
    socket.send(Communication::toFixedLengthString(
            8, OPCODE_CHARACTER_COUNT));
    _sendNode(node);
}

void GameClientSocket::_handleInitialData(YAML::Node &node) {
    std::vector<Communication::NameAndID> matches;
    std::vector<Communication::NameAndID> maps;
    for (const auto& match: node["matchs"]) {
        matches.emplace_back(
                match["name"].as<std::string>(),
                match["id"].as<int>());
    }
    for (const auto& map: node["maps"]) {
        maps.emplace_back(
                map["name"].as<std::string>(),
                map["id"].as<int>());
    }
    receiver.getInitialData(matches, maps);
}

void GameClientSocket::_handleGameState(YAML::Node &node) {
    Communication::GameState state;
    state.setState(node["state"].as<std::string>());
    for (const auto& enemy : node["enemies"]) {
        state.enemies.emplace_back(
                enemy["kind"].as<std::string>(),
                enemy["id"].as<int>(),
                enemy["position"]["x"].as<int>(),
                enemy["position"]["y"].as<int>());
    }
    for (const auto& tower : node["towers"]) {
        state.towers.emplace_back(
                tower["id"].as<int>(),
                Communication::Tower::Level(
                    tower["lv"]["range"].as<int>(),
                    tower["lv"]["damage"].as<int>(),
                    tower["lv"]["reach"].as<int>(),
                    tower["lv"]["slowdown"].as<int>()
                ),
                tower["xp"].as<int>(),
                tower["range_in_squares"].as<int>(),
                tower["explosion_range"].as<int>(),
                tower["position"]["x"].as<int>(),
                tower["position"]["y"].as<int>(),
                Communication::Tower::EnemySlowdown(
                        tower["enemy_slowdown"]["percentage"].as<int>(),
                        tower["enemy_slowdown"]["duration"].as<int>()),
                Communication::Tower::Damage(
                        tower["damage"]["normal"].as<int>(),
                        tower["damage"]["flying"].as<int>(),
                        tower["damage"]["close_by"].as<int>()),
                tower["element"].as<std::string>(),
                tower["is_attacking"].as<bool>(),
                tower["current_target"].as<int>()
        );
    }
    for (const auto& positionalPower : node["positional_powers"]) {
        state.positionalPowers.emplace_back(
                positionalPower["type"].as<std::string>(),
                positionalPower["position"]["x"].as<int>(),
                positionalPower["position"]["y"].as<int>()
        );
    }
    for (const auto& directedPower : node["directed_powers"]) {
        state.targetPowers.emplace_back(
                directedPower["type"].as<std::string>(),
                directedPower["enemy_id"].as<int>()
        );
    }
    receiver.getGameState(state);
}

void GameClientSocket::_handleRecievedMessage(YAML::Node &node) {
    std::string message = node["message"].as<std::string>();
    std::string nickname = node["nickname"].as<std::string>();
    receiver.getChatMessage(std::move(message), std::move(nickname));
}

void GameClientSocket::_handleUnavailableElement(YAML::Node &node) {
    std::string element = node["type"].as<std::string>();
    std::string username = node["username"].as<std::string>();
    receiver.getUnavailableElement(Communication::to_element(element),
                                   std::move(username));
}

GameClientSocket::GameClientSocket(GameClientSocket &&other) noexcept :
        receiver(other.receiver), socket(std::move(other.socket)) {}

void GameClientSocket::_handlePing(YAML::Node &node) {
    int x = node["x"].as<int>();
    int y = node["y"].as<int>();
    receiver.getPing(x, y);
}

GameClientSocket::~GameClientSocket() = default;
