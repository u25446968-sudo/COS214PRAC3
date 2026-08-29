#include "EventComponent.h"

EventComponent::EventComponent(const std::string& name) : name(name) {}

const std::string& EventComponent::getName() const {
    return name;
}

EventComponent::~EventComponent() {}