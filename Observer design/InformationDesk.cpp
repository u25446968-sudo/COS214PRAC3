#include "InformationDesk.h"

void InformationDesk::update(const Notice& notice){
    switch(notice.getType()){
        case NoticeType::WEATHER_ALERT:
          isOperational = true;
          break;
        case NoticeType::EVACUATE:
          isOperational = true;
          break;
        case NoticeType::CLOSE:
          isOperational = false;
          break;
        case NoticeType::OPEN:
            isOperational = true;
          break;
        case NoticeType::RESUME:
          isOperational = true;
          break;
        default:
          break;
    }
}