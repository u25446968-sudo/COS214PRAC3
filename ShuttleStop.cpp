#include "ShuttleStop.h"

void ShuttleStop::update(const Notice& notice)const{
    switch(notice.getType()){
      case WEATHER_ALERT:
        transportStatus = TransportStatus::DELAYED;
        break;
      case EVACUATE:
        transportStatus = TransportSTatus::HALTED;
        break;
      case TRANSPORT_DELAY:
        transportStatus = TransportSTatus::DELAYED;
        break;
      case RESUME:
        transportStatus = TransportSTatus::RUNNING;
        break;
      default:
        break;
    }
}