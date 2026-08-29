#include "EventControl.h"

void EventControl::issueNotice(NoticeType type, const std::string& message, int severity){
    Notice notice(type, message, severity);
    notify(notice);
}