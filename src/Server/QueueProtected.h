//
// Created by facundo on 31/10/17.
//

#ifndef TOWERDEFENSE_QUEUEPROTECTED_H
#define TOWERDEFENSE_QUEUEPROTECTED_H

#include <queue>
#include <mutex>
#include "Actions/Action.h"

class QueueProtected {
public:
    QueueProtected();
    ~QueueProtected();

    void push(Action* action);

    // libera la memoria alocada para el primer elemento y
    // lo elimina de la cola
    void pop();

    // retorna el primer elemento
    Action& front();

    bool empty();

    QueueProtected(const QueueProtected&) = delete;
    QueueProtected& operator=(const QueueProtected&) = delete;
    QueueProtected(QueueProtected&&) = delete;
    QueueProtected operator=(QueueProtected&&) = delete;

private:
    std::mutex mutex;
    std::queue<Action*> actions;
};


#endif //TOWERDEFENSE_QUEUEPROTECTED_H
