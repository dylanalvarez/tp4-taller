//
// Created by facundo on 30/10/17.
//

#include "GameServerReceiver.h"
#include "GameServerSocket.h"

GameServerSocket::GameServerSocket(GameServerReceiver& receiver,
                                   Socket &&socket) : receiver(receiver),
                                                      socket(std::move(socket)) {}

void GameServerSocket::sendGameState(
        const Communication::GameState &gameState) {
    YAML::Node game_node;

    game_node["state"] = Communication::GameState::to_string(gameState.state);

    game_node["enemies"];
    for (const Communication::Enemy& enemy : gameState.enemy) {
        YAML::Node enemy_node;
        enemy_node["id"] = enemy.id;
        YAML::Node position;
        position["x"] = enemy.x;
        position["y"] = enemy.y;
        enemy_node["position"] = position;
        enemy_node["kind"] = Communication::Enemy::to_string(enemy.type);

        game_node["enemies"].push_back(enemy_node);
    }

    game_node["towers"];
    for (const Communication::Tower& tower : gameState.towers) {
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

    game_node["positional_powers"];
    for (const Communication::PositionalPower& power: gameState.positionalPowers) {
        YAML::Node power_node;
        power_node["type"] = Communication::PositionalPower::to_string(power.type);
        YAML::Node position;
        position["x"] = power.x;
        position["y"] = power.y;
        power_node["position"] = position;

        game_node["positional_powers"].push_back(power_node);
    }

    game_node["positional_powers"];
    for (const Communication::TargetPower& power: gameState.targetPowers) {
        YAML::Node power_node;
        power_node["type"] = Communication::TargetPower::to_string(power.type);
        power_node["enemy_id"] = power.enemyID;

        game_node["directed_powers"].push_back(power_node);
    }
    YAML::Emitter emitter;
    emitter << game_node;
    std::string yaml_to_send(emitter.c_str());

    socket.send("3" + std::to_string(yaml_to_send.length()) + yaml_to_send);
}

GameServerSocket::GameServerSocket(GameServerSocket&& other) noexcept :
        receiver(other.receiver), socket(std::move(other.socket)) {}

GameServerSocket::~GameServerSocket() = default;
