#ifndef TP2_THREAD_H
#define TP2_THREAD_H

// clase madre de la cual , los "hilos" que seran ejecutados, heredan
// y redefinen el metodo run para realizar las tareas correspondientes

#include <thread>

class Thread {
private:
    std::thread thread;

public:
    void start();

    void join();

    virtual void run() = 0;

    virtual ~Thread();

    Thread(const Thread &) = delete;

    Thread &operator=(const Thread &) = delete;

    Thread(Thread &&) noexcept;

    Thread() = default;

    Thread &operator=(Thread &&) noexcept;
};


#endif //TP2_THREAD_H
