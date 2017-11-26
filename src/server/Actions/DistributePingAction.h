#ifndef TOWERDEFENSE_DISTRIBUTEPINGACTION_H
#define TOWERDEFENSE_DISTRIBUTEPINGACTION_H


#include "Action.h"

class DistributePingAction : public Action {
public:
    explicit DistributePingAction(Vector location);

    void apply(Context &context) override;

private:
    Vector location;
};


#endif //TOWERDEFENSE_DISTRIBUTEPINGACTION_H
