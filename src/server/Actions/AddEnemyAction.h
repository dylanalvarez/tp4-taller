#ifndef TOWERDEFENSE_ADDENEMYACTION_H
#define TOWERDEFENSE_ADDENEMYACTION_H


#include "Action.h"

class AddEnemyAction : public Action {
public:
    AddEnemyAction(const std::string &enemy_type, unsigned int path_number);

    void apply(Context &context) override;

    AddEnemyAction(const AddEnemyAction &) = delete;

    AddEnemyAction &operator=(const AddEnemyAction &) = delete;

private:
    std::string enemy_type;
    unsigned int path_number;
};


#endif //TOWERDEFENSE_ADDENEMYACTION_H
