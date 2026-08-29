#include "SecurityTeam.h"
#include <iostream>

SecurityTeam::SecurityTeam(const std::string& name, int capacity)
    : EventUnit(name, capacity), alertLevel(AlertLevel::NORMAL) {}

void SecurityTeam::reportStatus() const {
    std::string levelText = "NORMAL";
    if (alertLevel == AlertLevel::HEIGHTENED) {
        levelText = "HEIGHTENED";
    } else if (alertLevel == AlertLevel::EMERGENCY) {
        levelText = "EMERGENCY";
    }
    std::cout << "[Security] " << name << " - " << (isOpen ? "ACTIVE" : "STOOD DOWN")
              << ", alert level " << levelText
              << ", staff " << capacity << std::endl;
}