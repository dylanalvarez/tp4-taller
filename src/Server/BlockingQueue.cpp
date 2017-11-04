//
// Created by facundo on 09/09/17.
//

#include <iostream>
#include "BlockingQueue.h"

BlockingQueue::BlockingQueue() = default;

BlockingQueue::~BlockingQueue() {
    while (!queue.empty()) {
        delete queue.front();
        queue.pop();
    }
}

void BlockingQueue::push(Action* action){
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(action);
    is_there_something.notify_one();
}

Action& BlockingQueue::front() {
    std::unique_lock<std::mutex> lock(mutex);
    while (queue.empty()) {
        // dado que existe un "bug" en wait y puede
        // "despertarse" sin un signal se lo encapsula en un while
        is_there_something.wait(lock);
    }
    return *queue.front();
}

bool BlockingQueue::empty() {
    return queue.empty();
}

void BlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    delete queue.front();
    queue.pop();
}

BlockingQueue::BlockingQueue(BlockingQueue&& other) noexcept {
    std::unique_lock<std::mutex> lock(mutex);
    this->queue = std::move(other.queue);
}

BlockingQueue &BlockingQueue::operator=(BlockingQueue&& other) noexcept {
    std::unique_lock<std::mutex> lock(mutex);
    this->queue = std::move(other.queue);
    return *this;
}
