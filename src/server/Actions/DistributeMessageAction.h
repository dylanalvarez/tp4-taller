#ifndef TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H
#define TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H


#include "Action.h"

class DistributeMessageAction : public Action {
public:
    explicit DistributeMessageAction(std::string &&msg,
                                     const std::string &nickname);

    void apply(Context &contex) override;

private:
    std::string msg;
    const std::string &nickname;
};


#endif //TOWERDEFENSE_DISTRIBUTEMESSAGEACTION_H
