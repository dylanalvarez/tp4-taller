#ifndef TOWERDEFENSE_SENDMESSAGEACTION_H
#define TOWERDEFENSE_SENDMESSAGEACTION_H


#include "Action.h"

class SendMessageAction : public Action {
public:
    explicit SendMessageAction(const std::string &msg,
                               const std::string &nickname);

    void apply(Context &context) override;

    SendMessageAction(const SendMessageAction &) = delete;

    SendMessageAction &operator=(const SendMessageAction &) = delete;

private:
    std::string msg;
    const std::string &name;
};


#endif //TOWERDEFENSE_SENDMESSAGEACTION_H
