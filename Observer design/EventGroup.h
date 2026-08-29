#ifndef EVENTGROUP_H
#define EVENTGROUP_H

#include "EventComponent.h"
#include "Subject.h"
#include "Observer.h"

class EventGroup : public EventComponent, Subject, Observer{
    void update(const Notice& notice)override;
};

#endif
