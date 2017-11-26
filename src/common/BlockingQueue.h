#ifndef TP2_BLOCKINGQUEUE_H
#define TP2_BLOCKINGQUEUE_H


#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>
#include "../server/Actions/Action.h"

// BlockingQueue es una estructura de datos bloqueante.
// Cuando un thread intenta sacar un elemento y esta vacia, es
// bloqueado con "wait" hasta que otro thread realiza un push sobre
// la estructura.

class BlockingQueue {
public:
    BlockingQueue();

    ~BlockingQueue();

    // inserta elemento en la cola y libera al thread que fue bloqueado
    // por front
    void push(Action *action);

    // extrae el elemento que esta al "frente", es decir el primero de la cola
    // si la cola esta vacia bloquea el thread invocante con wait
    Action &front();

    // remueve el primer elemento y libera sus recursos
    void pop();

    bool empty();

    BlockingQueue(const BlockingQueue &) = delete;

    BlockingQueue &operator=(const BlockingQueue &) = delete;

    BlockingQueue(BlockingQueue &&) noexcept;

    BlockingQueue &operator=(BlockingQueue &&) noexcept;

private:
    std::queue<Action *> queue;
    std::mutex mutex;
    std::condition_variable is_there_something;
};

#endif //TP2_BLOCKINGQUEUE_H
