#include "InformationDesk.h"
#include <iostream>

InformationDesk::InformationDesk(const std::string& name)
    : EventUnit(name, 0) {}

int InformationDesk::getCapacity() const {
    return 0;
}

void InformationDesk::reportStatus() const {
    std::cout << "[InfoDesk] " << name << " - " << (isOpen ? "STAFFED" : "UNSTAFFED") << std::endl;
}