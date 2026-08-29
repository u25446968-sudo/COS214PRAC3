#ifndef SHUTTLE_STOP_H
#define SHUTTLE_STOP_H

#include "EventUnit.h"

enum class TransportStatus {
    RUNNING,
    HALTED,
    DELAYED
};

class ShuttleStop : public EventUnit {
private:
    TransportStatus transportStatus;

public:
    ShuttleStop(const std::string& name, int capacity);
    void reportStatus() const override;
};

#endif