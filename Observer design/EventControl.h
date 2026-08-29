#ifndef EVENTCONTROL_H
#define EVENTCONTROL_H

#include "Subject.h"

class EventControl : public Subject{
    public:
      void issueNotice(NoticeType type, const std::string& message, int severity=0);
}

#endif