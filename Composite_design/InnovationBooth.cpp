#include "InnovationBooth.h"
#include <iostream>

InnovationBooth::InnovationBooth(const std::string& name, int capacity, const std::string& exhibitorName)
    : EventUnit(name, capacity), exhibitorName(exhibitorName) {}

void InnovationBooth::reportStatus() const {
    std::cout << "[Booth] " << name << " (" << exhibitorName << ") - "
              << (isOpen ? "OPEN" : "CLOSED")
              << ", capacity " << capacity << std::endl;
}