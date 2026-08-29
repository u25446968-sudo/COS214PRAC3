#ifndef EVENT_UNIT_H
#define EVENT_UNIT_H

#include "EventComponent.h"
#include "Observer.h"
#include "Notice.h"

class EventUnit : public EventComponent, public Observer {
protected:
    int capacity;
    bool isOpen;

public:
    EventUnit(const std::string& name, int capacity);

    void open() override;

    void close() override;

    int getCapacity() const override;

    void update(const Notice& notice) override;

    virtual ~EventUnit();
};
#endif