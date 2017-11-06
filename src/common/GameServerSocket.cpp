//
// Created by facundo on 30/10/17.
//

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "GameServerReceiver.h"
#include "GameServerSocket.h"

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
        tower_node["lv"] = tower.level;
        tower_node["xp"] = tower.experience;
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
    YAML::Emitter emitter;
    emitter << game_node;
    std::string yaml_to_send(emitter.c_str());

    socket.send(Communication::toFixedLengthString(3, OPCODE_CHARACTER_COUNT));
    socket.send(Communication::toFixedLengthString(
            yaml_to_send.length(),
            MESSAGE_LENGTH_CHARACTER_COUNT));
    socket.send(yaml_to_send);
}

GameServerSocket::GameServerSocket(GameServerSocket &&other) noexcept :
        receiver(other.receiver), socket(std::move(other.socket)) {}

void GameServerSocket::sendChatMessage(
        std::string &&message,
        std::string &nickname) {
    YAML::Node initialData;
    initialData["message"] = message;
    initialData["nickname"] = nickname;
    YAML::Emitter emitter;
    emitter << initialData;
    std::string yaml_to_send(emitter.c_str());
    socket.send(Communication::toFixedLengthString(4, OPCODE_CHARACTER_COUNT));
    socket.send(Communication::toFixedLengthString(
            yaml_to_send.length(),
            MESSAGE_LENGTH_CHARACTER_COUNT));
    socket.send(yaml_to_send);
}

void GameServerSocket::sendInitialData(
        const std::vector<Communication::NameAndID> &matches,
        const std::vector<Communication::NameAndID> &maps) {
    YAML::Node initialData;
    initialData["matches"];
    for (auto &match : matches) {
        YAML::Node matchNode;
        matchNode["id"] = match.id;
        matchNode["name"] = match.name;
        initialData["matches"].push_back(matchNode);
    }
    initialData["maps"];
    for (auto &map : maps) {
        YAML::Node mapNode;
        mapNode["id"] = map.id;
        mapNode["name"] = map.name;
        initialData["matches"].push_back(mapNode);
    }
    YAML::Emitter emitter;
    emitter << initialData;
    std::string yaml_to_send(emitter.c_str());

    socket.send(Communication::toFixedLengthString(0, OPCODE_CHARACTER_COUNT));
    socket.send(Communication::toFixedLengthString(
            yaml_to_send.length(),
            MESSAGE_LENGTH_CHARACTER_COUNT));
    socket.send(yaml_to_send);
}

void GameServerSocket::sendMap(std::string &&filename) {
    std::ifstream file(filename);
    socket.send(std::string(std::istreambuf_iterator<char>(file),
                            std::istreambuf_iterator<char>()));
}

GameServerSocket::~GameServerSocket() = default;

void GameServerSocket::run() {
    while (keep_running) {
        // recibir opcode y llamar a receiver
    }
}

void GameServerSocket::disconnect() {
    keep_running = false;
}

void GameServerSocket::sendPing(int x, int y) {

}
