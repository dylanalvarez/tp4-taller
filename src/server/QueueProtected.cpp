//
// Created by facundo on 31/10/17.
//

#include "QueueProtected.h"

QueueProtected::QueueProtected() = default;

QueueProtected::~QueueProtected() = default;

void QueueProtected::push(Action* action) {
    std::lock_guard<std::mutex> lock(mutex);
    actions.push(action);
}

void QueueProtected::pop() {
    std::lock_guard<std::mutex> lock(mutex);
    delete actions.front();
    actions.pop();
}

Action &QueueProtected::front() {
    return *actions.front();
}

bool QueueProtected::empty() {
    std::lock_guard<std::mutex> lock(mutex);
    return actions.empty();
}

QueueProtected::QueueProtected(QueueProtected&& other) noexcept {
    std::lock_guard<std::mutex> lock(mutex);
    this->actions = std::move(other.actions);
}

QueueProtected& QueueProtected::operator=(QueueProtected&& other) noexcept {
    std::lock_guard<std::mutex> lock(mutex);
    this->actions = std::move(other.actions);
    return *this;
}
