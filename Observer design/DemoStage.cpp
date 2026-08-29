#include "DemoStage.h"


void DemoStage::update(const Notice& notice){
    switch(notice.getType()){
        case NoticeType::WEATHER_ALERT:
          isPaused = true;
          break;
        case NoticeType::EVACUATE:
          isPaused = true;
          break;
        case NoticeType::RESUME:
          isPaused = false;
          break; 
        default:
          break;
    }
}
