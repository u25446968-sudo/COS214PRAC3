#include "Notice.h"

Notice::Notice(NoticeType type, std::string message, int severity = 0){
    this->type = type;
    this->message = message;
    this->severity = severity;
}
NoticeType Notice::getType()const{
    return type;
}
const std::string& getMessage()const{
    return message;
}
int getSeverity()const{
    return severity;
}