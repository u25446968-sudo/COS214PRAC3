#ifndef FOODVENDOR_H
#define FOODVENDOR_H

#include "Observer.h"
#include "EventUnit.h"

class FoodVendor : public EventUnit, public Observer{
    private:
       bool isOpened;
    public: 
       void update(const Notice& notice)override;
};

#endif