#ifndef DEMO_STAGE_H
#define DEMO_STAGE_H

#include "EventUnit.h"

class DemoStage : public EventUnit {
private:
    int queueLength;
    bool isPaused;
    int scheduleVersion;

public:
    DemoStage(const std::string& name, int capacity);
    void joinQueue();
    void close() override;
    void reportStatus() const override;
};

#endif