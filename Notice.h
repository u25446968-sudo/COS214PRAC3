#ifndef NOTICE_H
#define NOTICE_H

#include <string>

enum class NoticeType{
    OPEN, CLOSE, CAPACITY_ALERT, WEATHER_ALERT, TRANSPORT_DELAY, EVACUATE, RESUME
};

class Notice{
    private:
      NoticeType type;
      std::string message;
      int severity;
    public: 
      Notice(NoticeType type, std::string message, int severity = 0);
      NoticeType getType()const;
      const std::string& getMessage()const;
      int getSeverity()const;

};

#endif