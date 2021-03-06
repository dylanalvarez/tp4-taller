#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "GameServerReceiver.h"
#include "GameServerSocket.h"
#include "Exception.h"

GameServerSocket::GameServerSocket(GameServerReceiver &receiver,
                                   Socket &&socket)
        : receiver(receiver), socket(std::move(socket)), keep_running(true) {}

void GameServerSocket::sendGameState(
        const Communication::GameState &gameState) {
    YAML::Node game_node;

    game_node["state"] = Communication::GameState::to_string(gameState.state);

    game_node["enemies"] = YAML::Load("[ ]");
    for (const Communication::Enemy &enemy : gameState.enemies) {
        YAML::Node enemy_node;
        enemy_node["id"] = enemy.id;
        YAML::Node position;
        position["x"] = enemy.x;
        position["y"] = enemy.y;
        enemy_node["position"] = position;
        enemy_node["kind"] = Communication::Enemy::to_string(enemy.type);

        game_node["enemies"].push_back(enemy_node);
    }

    game_node["towers"] = YAML::Load("[ ]");
    for (const Communication::Tower &tower : gameState.towers) {
        YAML::Node tower_node;

        tower_node["id"] = tower.id;
        tower_node["element"] = Communication::Tower::to_string(tower.type);
        tower_node["xp"] = tower.experience;
        YAML::Node level;
        level["range"] = tower.level.range;
        level["damage"] = tower.level.damage;
        level["reach"] = tower.level.reach;
        level["slowdown"] = tower.level.slowdown;
        tower_node["lv"] = level;
        YAML::Node damage;
        damage["normal"] = tower.damage.normal;
        damage["flying"] = tower.damage.flying;
        damage["close_by"] = tower.damage.close_by;
        tower_node["damage"] = damage;
        YAML::Node slowdown;
        slowdown["percentage"] = tower.slowdown.percentage;
        slowdown["duration"] = tower.slowdown.duration;
        tower_node["enemy_slowdown"] = slowdown;
        tower_node["range_in_squares"] = tower.rangeInSquares;
        tower_node["explosion_range"] = tower.ExplosionRange;
        YAML::Node position;
        position["x"] = tower.x;
        position["y"] = tower.y;
        tower_node["position"] = position;
        tower_node["is_attacking"] = tower.is_attacking;
        tower_node["current_target"] = tower.current_target_id;

        game_node["towers"].push_back(tower_node);
    }

    game_node["positional_powers"] = YAML::Load("[ ]");
    for (const Communication::PositionalPower &power: gameState.positionalPowers) {
        YAML::Node power_node;
        power_node["type"] = Communication::PositionalPower::to_string(
                power.type);
        YAML::Node position;
        position["x"] = power.x;
        position["y"] = power.y;
        power_node["position"] = position;

        game_node["positional_powers"].push_back(power_node);
    }

    game_node["directed_powers"] = YAML::Load("[ ]");
    for (const Communication::TargetPower &power: gameState.targetPowers) {
        YAML::Node power_node;
        power_node["type"] = Communication::TargetPower::to_string(power.type);
        power_node["enemy_id"] = power.enemyID;

        game_node["directed_powers"].push_back(power_node);
    }

    try {
        socket.send(
                Communication::toFixedLengthString(3, OPCODE_CHARACTER_COUNT));
        sendNode(game_node);
    } catch (Exception &e) {}

}

GameServerSocket::GameServerSocket(GameServerSocket &&other) noexcept :
        receiver(other.receiver),
        socket(std::move(other.socket)),
        keep_running(other.keep_running) {}

void GameServerSocket::sendChatMessage(
        const std::string &message,
        const std::string &nickname) {
    YAML::Node msg;
    msg["message"] = message;
    msg["nickname"] = nickname;
    try {
        socket.send(Communication::toFixedLengthString(4, OPCODE_CHARACTER_COUNT));
        sendNode(msg);
    } catch (Exception& e) {}
}

void GameServerSocket::sendInitialData(
        const std::vector<Communication::NameAndID> &matches,
        const std::vector<Communication::NameAndID> &maps) {
    YAML::Node initialData;
    initialData["matches"] = YAML::Load("[ ]");
    for (auto &match : matches) {
        YAML::Node matchNode;
        matchNode["id"] = match.id;
        matchNode["name"] = match.name;
        initialData["matchs"].push_back(matchNode);
    }
    initialData["maps"] = YAML::Load("[ ]");
    for (auto &map : maps) {
        YAML::Node mapNode;
        mapNode["id"] = map.id;
        mapNode["name"] = map.name;
        initialData["maps"].push_back(mapNode);
    }

    try {
        socket.send(Communication::toFixedLengthString(0, OPCODE_CHARACTER_COUNT));
        sendNode(initialData);
    } catch (Exception& e) {}
}

void GameServerSocket::makeElementUnavailable(Communication::Element element,
                                              const std::string &username) {
    YAML::Node node;
    node["type"] = Communication::to_string(element);
    node["username"] = username;
    socket.send(Communication::toFixedLengthString(
            6, OPCODE_CHARACTER_COUNT));
    sendNode(node);
}

void GameServerSocket::sendMap(const std::string &filename) {
    std::ifstream file(filename);
    std::string content(static_cast<std::stringstream const &>(
                                std::stringstream() << file.rdbuf()).str());
    try {
        socket.send(Communication::toFixedLengthString(2, OPCODE_CHARACTER_COUNT));
        socket.send(Communication::toFixedLengthString(
                content.length(), MESSAGE_LENGTH_CHARACTER_COUNT));
        socket.send(content);
    } catch (Exception& e) {}
}

GameServerSocket::~GameServerSocket() = default;

void GameServerSocket::run() {
    while (keep_running) {
        try {
            std::string str_opcode = socket.receiveString(
                    OPCODE_CHARACTER_COUNT);
            if (str_opcode.empty()) {
                keep_running = false;
                break;
            }
            int opcode = std::stoi(str_opcode);
            unsigned long messageLength = std::stoul(
                    socket.receiveString(MESSAGE_LENGTH_CHARACTER_COUNT));
            std::string messageAsString = socket.receiveString(messageLength);
            switch (opcode) {
                case 0:
                    handleChosenMatch(messageAsString);
                    break;
                case 1:
                    handleChosenMap(messageAsString);
                    break;
                case 2:
                    handleChosenElement(messageAsString);
                    break;
                case 3:
                    receiver.startMatch();
                    break;
                case 4:
                    handleSendMessage(messageAsString);
                    break;
                case 5:
                    handlePingTile(messageAsString);
                    break;
                case 6:
                    handleSpell(messageAsString);
                    break;
                case 7:
                    handleUpgrade(messageAsString);
                    break;
                case 8:
                    handleBuildTower(messageAsString);
                    break;
                default:
                    break;
            }
        } catch (Exception &e) {
            //socket cerrado
            keep_running = false;
        }
    }
}

void GameServerSocket::disconnect() {
    keep_running = false;
}

void GameServerSocket::sendPing(int x, int y) {
    YAML::Node ping_node;
    ping_node["x"] = x;
    ping_node["y"] = y;
    socket.send(Communication::toFixedLengthString(5, OPCODE_CHARACTER_COUNT));
    sendNode(ping_node);
}

void GameServerSocket::handleChosenMap(std::string &yaml) {
    YAML::Node chosen_map = YAML::Load(yaml);
    auto map_id = chosen_map["id"].as<int>();
    std::string nickname = chosen_map["nickname"].as<std::string>();
    std::string mapName = chosen_map["map_name"].as<std::string>();
    receiver.createMatch(map_id, nickname, mapName);
}

void GameServerSocket::handleChosenMatch(std::string &yaml) {
    YAML::Node chosen_match = YAML::Load(yaml);
    auto match_id = chosen_match["id"].as<int>();
    std::string nickname = chosen_match["nickname"].as<std::string>();
    receiver.joinMatch(match_id, nickname);
}

void GameServerSocket::handleChosenElement(std::string &yaml) {
    YAML::Node element_node = YAML::Load(yaml);
    std::string element = element_node["type"].as<std::string>();
    receiver.getChosenElement(Communication::to_element(element));
}

void GameServerSocket::handleSendMessage(std::string &yaml) {
    YAML::Node msg_node = YAML::Load(yaml);
    std::string message = msg_node["message"].as<std::string>();

    receiver.getChatMessage(std::move(message));
}

void GameServerSocket::handlePingTile(std::string &yaml) {
    YAML::Node ping_node = YAML::Load(yaml);
    receiver.getPingedTile(ping_node["x"].as<int>(), ping_node["y"].as<int>());
}

void GameServerSocket::handleSpell(std::string &yaml) {
    YAML::Node spell_node = YAML::Load(yaml);
    std::string type = spell_node["type"].as<std::string>();
    std::vector<std::string> positional_spells{"terraforming",
                                               "fissure",
                                               "fireWall",
                                               "blizzard",
                                               "tornado"};
    if (std::find(positional_spells.begin(), positional_spells.end(), type)
        != positional_spells.end()) {
        // is positional
        auto x = spell_node["position"]["x"].as<int>();
        auto y = spell_node["position"]["y"].as<int>();
        receiver.getSpell(Communication::PositionalPower(type, x, y));
    } else {
        // is target
        auto enemy_id = spell_node["enemy_id"].as<int>();
        receiver.getSpell(Communication::TargetPower(type, enemy_id));
    }
}

void GameServerSocket::handleUpgrade(std::string &yaml) {
    YAML::Node upgrade_node = YAML::Load(yaml);

    auto tower_id = upgrade_node["tower_id"].as<int>();
    std::string type = upgrade_node["type"].as<std::string>();

    receiver.getUpgrade(Communication::Upgrade(type, tower_id));
}

void GameServerSocket::handleBuildTower(std::string &yaml) {
    YAML::Node build_node = YAML::Load(yaml);
    auto x = build_node["position"]["x"].as<int>();
    auto y = build_node["position"]["y"].as<int>();
    std::string type = build_node["type"].as<std::string>();
    receiver.buildTower(x, y, Communication::Tower::string_to_type(type));
}

void GameServerSocket::sendNode(YAML::Node &node) {
    YAML::Emitter emitter;
    emitter << node;
    std::string message(emitter.c_str());
    
    try {
        socket.send(Communication::toFixedLengthString(
                message.length(), MESSAGE_LENGTH_CHARACTER_COUNT));
        socket.send(message);
    } catch (Exception& e) {}
}

bool GameServerSocket::isOperational() const {
    return keep_running;
}
