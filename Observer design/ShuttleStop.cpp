#include "ShuttleStop.h"

void ShuttleStop::update(const Notice& notice){
    switch(notice.getType()){
      case WEATHER_ALERT:
        transportStatus = TransportStatus::DELAYED;
        break;
      case EVACUATE:
        transportStatus = TransportStatus::HALTED;
        break;
      case TRANSPORT_DELAY:
        transportStatus = TransportStatus::DELAYED;
        break;
      case RESUME:
        transportStatus = TransportStatus::RUNNING;
        break;
      default:
        break;
    }
}