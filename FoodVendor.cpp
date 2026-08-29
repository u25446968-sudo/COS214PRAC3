#include "FoodVendor.h"

void FoodVendor::update(const Notice& notice){
     switch(notice.getType()){
        case NoticeType::WEATHER_ALERT:
          isOpen = false;
          break;
        case NoticeType::EVACUATE:
          isOpen = false;
          break;
        case NoticeType::CLOSE:
          isOpen = false;
          break;
        case NoticeType::OPEN:
            isOperational = true;
          break;
        case NoticeType::RESUME:
          isOperational = true;
          break;
        case NoticeType::CAPACITY_ALERT:
          isOpen = false;
          break;
        default:
          break;
    }
}