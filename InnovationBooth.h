#ifndef INNOVATIONBOOTH_H
#define INNOVATIONBOOTH_H

#include "Observer.h"
#include "EventUnit.h"

class InnovationBooth : public EventUnit, public Observer{
    private:
       bool isDisplaying;
    public: 
       void update(const Notice& notice)override;
};

#endif