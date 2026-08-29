#include "EventUnit.h"
#include <iostream>

EventUnit::EventUnit(const std::string& name, int capacity)
    : EventComponent(name), capacity(capacity), isOpen(false) {}

void EventUnit::open() {
    isOpen = true;
}

void EventUnit::close() {
    isOpen = false;
}

int EventUnit::getCapacity() const {
    return capacity;
}

void EventUnit::update(const Notice& notice) {
    std::cout << name << " received notice: " << notice.detail << std::endl;
}

EventUnit::~EventUnit() {
    std::cout << "Releasing unit: " << name << std::endl;
}