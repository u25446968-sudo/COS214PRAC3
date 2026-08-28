#include "SecurityTeam.h"

void SecurityTeam::update(const Notice& notice)const{
    switch(notice.getType()){
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