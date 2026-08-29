#include "ShuttleStop.h"
#include <iostream>

ShuttleStop::ShuttleStop(const std::string& name, int capacity)
    : EventUnit(name, capacity), transportStatus(TransportStatus::RUNNING) {}

void ShuttleStop::reportStatus() const {
    std::string statusText = "RUNNING";
    if (transportStatus == TransportStatus::HALTED) {
        statusText = "HALTED";
    } else if (transportStatus == TransportStatus::DELAYED) {
        statusText = "DELAYED";
    }
    std::cout << "[Shuttle] " << name << " - " << (isOpen ? "OPEN" : "CLOSED")
              << ", transport " << statusText
              << ", capacity " << capacity << std::endl;
}