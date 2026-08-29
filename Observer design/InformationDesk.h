#ifndef INFORMATIONDESK_H
#define INFORMATIONDESK_H

#include "Observer.h"
#include "EventUnit.h"

class InformationDesk : public EventUnit, public Observer{
    private:
       bool isOperation;
    public: 
       void update(const Notice& notice)override;
};

#endif