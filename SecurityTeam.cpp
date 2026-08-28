#include "SecurityTeam.h"

void SecurityTeam::update(const Notice& notice){
    switch(notice.getType()){
      case WEATHER_ALERT:
        alertLevel = AlertLevel::HEIGHTENED;
        break;
      case CAPACITY_ALERT:
        alertLevel = AlertLevel::HEIGHTENED;
        break;
      case EVACUATE:
        alertLevel = AlertLevel::EMERGENCY;
        break;
      case RESUME:
        alertLevel = AlertLevel::NORMAL;
        break;
      default:
        break;
    }
}