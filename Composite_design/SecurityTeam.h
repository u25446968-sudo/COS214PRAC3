#ifndef SECURITY_TEAM_H
#define SECURITY_TEAM_H

#include "EventUnit.h"

enum class AlertLevel {
    NORMAL,
    HEIGHTENED,
    EMERGENCY
};

class SecurityTeam : public EventUnit {
private:
    AlertLevel alertLevel;

public:
    SecurityTeam(const std::string& name, int capacity);
    void reportStatus() const override;
};

#endif