//
// Created by facundo on 30/10/17.
//

#include "GameServerReceiver.h"
#include "../server/Server.h"
#include "../server/Actions/DistributeMessageAction.h"
#include "../server/Actions/ThrowPositionalSpellAction.h"
#include "../server/Actions/ThrowTargetSpellAction.h"
#include "../server/Actions/BuildTowerAction.h"
#include "../server/Actions/UpgradeAction.h"
#include "../server/Actions/DistributePingAction.h"

GameServerReceiver::GameServerReceiver(Server &server, Client& client) :
        server(server), client(client) {}

GameServerReceiver::GameServerReceiver(GameServerReceiver&& other) noexcept :
        server(other.server),
        client(other.client) {}

void GameServerReceiver::setActionsQueue(QueueProtected &queue) {
    actions_queue = &queue;
}

void GameServerReceiver::joinMatch(int match_id,
                                   const std::string &player_name) {
    client.setName(player_name);
    server.joinMatch(client, match_id);
    my_match_id = match_id;
}

void GameServerReceiver::createMatch(int map_id,
                                     const std::string &player_name) {
    client.setName(player_name);
    my_match_id = server.createMatch(client, map_id);
    client.setReady();
    server.startMatch(my_match_id);
}

void GameServerReceiver::startMatch() {
    client.setReady();
    server.startMatch(my_match_id);
}

void GameServerReceiver::getChosenElement(Communication::Element element) {
    server.addElementToPlayer(client, my_match_id,
                              Communication::to_string(element));
}

void GameServerReceiver::getChatMessage(std::string &&message,
                                        std::string&& nickname) {
    actions_queue->push(new DistributeMessageAction(std::move(message),
                                                    std::move(nickname)));
}

void GameServerReceiver::getSpell(Communication::PositionalPower power) {
    std::string power_name =
            Communication::PositionalPower::to_string(power.type);
    Vector position(power.x, power.y);
    actions_queue->push(new ThrowPositionalSpellAction(power_name,
                                                       client.getModelPlayer(),
                                                       position));
}

void GameServerReceiver::getSpell(Communication::TargetPower power) {
    std::string power_name =
            Communication::TargetPower::to_string(power.type);
    actions_queue->push(new ThrowTargetSpellAction(power_name,
                                                   client.getModelPlayer(),
                                                   power.enemyID));
}

void GameServerReceiver::getUpgrade(Communication::Upgrade upgrade) {
    const std::vector<const Tower*> towers =
            client.getModelPlayer().getTowers();
    const Tower* tower = nullptr;
    for (const Tower* t : towers) {
        if (t->getID() == upgrade.towerID) { tower = t; break;}
    }
    if (!tower) { return; }

    std::string upgrade_name = Communication::Upgrade::to_string(upgrade.type);
    actions_queue->push(new UpgradeAction(client.getModelPlayer(),
                                          *tower, upgrade_name));
}

void GameServerReceiver::buildTower(int x, int y,
                                    Communication::Tower::Type type) {
    std::string tower_type = Communication::Tower::to_string(type);
    actions_queue->push(new BuildTowerAction(client.getModelPlayer(),
                                             tower_type,
                                             Vector(x, y)));
}

void GameServerReceiver::getPingedTile(int x, int y) {
    actions_queue->push(new DistributePingAction(Vector(x, y)));
}

GameServerReceiver::~GameServerReceiver() = default;
