#ifndef SECURITYTEAM_H
#define SECURITYTEAM_H

#include "Observer.h"
#include "EventUnit.h"

enum class AlertLevel {NORMAL, HEIGHTENED, EMERGENCY};

class SecurityTeam : public EventUnit, public Observer{
    private:
       AlertLevel alertLevel;
    public: 
       void update(const Notice& notice)override;
};

#endif