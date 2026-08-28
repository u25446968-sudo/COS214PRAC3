#ifndef DEMOSTAGE_H
#define DEMOSTAGE_H

#include "Observer.h"
#include "EventUnit.h"

class DemoStage : public EventUnit, public Observer{
    private:
       bool isPaused;
    public: 
       void update(const Notice& notice)override;
};

#endif