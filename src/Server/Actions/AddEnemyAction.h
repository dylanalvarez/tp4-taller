//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_ADDENEMYACTION_H
#define TOWERDEFENSE_ADDENEMYACTION_H


#include "Action.h"

class AddEnemyAction : public Action {
public:
    AddEnemyAction(std::string& enemy_type, unsigned int path_number);

    void apply(Context& context) override;

    AddEnemyAction(const AddEnemyAction&) = delete;
    AddEnemyAction& operator=(const AddEnemyAction&) = delete;

private:
    std::string enemy_type;
    unsigned int path_number;
};


#endif //TOWERDEFENSE_ADDENEMYACTION_H
