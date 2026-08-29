#include "DemoStage.h"
#include <iostream>

DemoStage::DemoStage(const std::string& name, int capacity)
    : EventUnit(name, capacity), queueLength(0), isPaused(false), scheduleVersion(0) {}

void DemoStage::joinQueue() {
    queueLength++;
}

void DemoStage::close() {
    isOpen = false;
    queueLength = 0;
}

void DemoStage::reportStatus() const {
    std::cout << "[Demo] " << name << " - " << (isOpen ? "OPEN" : "CLOSED")
              << (isPaused ? " (paused)" : "")
              << ", queue " << queueLength << "/" << capacity
              << ", schedule v" << scheduleVersion << std::endl;
}