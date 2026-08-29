#ifndef FOOD_VENDOR_H
#define FOOD_VENDOR_H

#include "EventUnit.h"

class FoodVendor : public EventUnit {
private:
    bool needsInspection;

public:
    FoodVendor(const std::string& name, int capacity, bool needsInspection);
    void reportStatus() const override;
};

#endif