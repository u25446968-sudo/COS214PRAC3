#include "EventGroup.h"
#include <iostream>

EventGroup::EventGroup(const std::string& name) : EventComponent(name) {}

void EventGroup::add(EventComponent* component) {
    if (component != nullptr) {
        children.push_back(component);
    }
}

void EventGroup::remove(EventComponent* component) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == component) {
            children.erase(it);
            return;
        }
    }
}

void EventGroup::open() {
    for (EventComponent* c : children) {
        c->open();
    }
}

void EventGroup::close() {
    for (EventComponent* c : children) {
        c->close();
    }
}

void EventGroup::reportStatus() const {
    std::cout << "[Zone] " << name << ":" << std::endl;
    for (EventComponent* c : children) {
        c->reportStatus();
    }
}

int EventGroup::getCapacity() const {
    int total = 0;
    for (EventComponent* c : children) {
        total += c->getCapacity();
    }
    return total;
}

void EventGroup::attach(Observer* observer) {
    if (observer == nullptr) {
        return;
    }
    for (Observer* o : observers) {
        if (o == observer) {
            return;
        }
    }
    observers.push_back(observer);
}

void EventGroup::detach(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void EventGroup::notify() {
    for (Observer* o : observers) {
        o->update(currentNotice);
    }
}

void EventGroup::update(const Notice& notice) {
    std::cout << "[Zone] " << name << " relaying notice: " << notice.detail << std::endl;
    issueNotice(notice);
}

void EventGroup::issueNotice(const Notice& notice) {
    currentNotice = notice;
    notify();
}

EventGroup::~EventGroup() {
    std::cout << "Releasing zone: " << name << std::endl;
    for (EventComponent* c : children) {
        delete c;
    }
    children.clear();
}