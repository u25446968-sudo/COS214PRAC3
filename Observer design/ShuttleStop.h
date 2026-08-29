#ifndef SHUTTLESTOP_H
#define SHUTTLESTOP_H

#include "Observer.h"
#include "EventUnit.h"

enum class TransportStatus {RUNNING, HALTED, DELAYED};

class ShuttleStop : public EventUnit, public Observer{
    private:
       TransportStatus transportStatus;
    public: 
       void update(const Notice& notice)override;
};

#endif