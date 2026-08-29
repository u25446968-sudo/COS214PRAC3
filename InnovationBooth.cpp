#include "InnovationBooth.h"

void InnovationBooth::update(const Notice& notice){
    switch(notice.getType()){
        case NoticeType::WEATHER_ALERT:
          isDisplaying = false;
          break;
        case NoticeType::EVACUATE:
          isDisplaying = false;
          break;
        case NoticeType::CAPACITY_ALERT:
          isDisplaying = false;
          break;
        case NoticeType::OPEN:
            isDisplaying = true;
          break;
        case NoticeType::RESUME:
          isDisplaying = true;
          break;
        default:
          break;
    }
}