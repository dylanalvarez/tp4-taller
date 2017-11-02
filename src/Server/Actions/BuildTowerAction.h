//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_BUILDTOWERACTION_H
#define TOWERDEFENSE_BUILDTOWERACTION_H


#include "Action.h"
#include "../../model/Player.h"

class BuildTowerAction : public Action {
public:
    BuildTowerAction(const Player& player, std::string& element,
                     Vector position);

    void apply(TowerDefenseGame& game) override;

    BuildTowerAction(const BuildTowerAction&) = delete;
    BuildTowerAction& operator=(const BuildTowerAction&) = delete;

private:
    const Player& player;
    std::string element;
    Vector position;
};


#endif //TOWERDEFENSE_BUILDTOWERACTION_H
