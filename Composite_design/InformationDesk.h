#ifndef INFORMATION_DESK_H
#define INFORMATION_DESK_H

#include "EventUnit.h"

class InformationDesk : public EventUnit {
public:
    explicit InformationDesk(const std::string& name);
    int getCapacity() const override;
    void reportStatus() const override;
};

#endif