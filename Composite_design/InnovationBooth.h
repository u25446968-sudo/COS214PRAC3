#ifndef INNOVATION_BOOTH_H
#define INNOVATION_BOOTH_H

#include "EventUnit.h"

class InnovationBooth : public EventUnit {
private:
    std::string exhibitorName;

public:
    InnovationBooth(const std::string& name, int capacity, const std::string& exhibitorName);
    void reportStatus() const override;
};

#endif