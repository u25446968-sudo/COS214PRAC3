#ifndef EVENT_COMPONENT_H
#define EVENT_COMPONENT_H

#include <string>


class EventComponent{

    protected:
     std::string name;


    public:

    EventComponent(const std::string& name);

    virtual void open()=0;

    virtual void close()=0;

    virtual void reportStatus() const=0;

    virtual int getCapacity() const =0;

    const std::string& getName() const;

    virtual ~EventComponent();


}


#endif  /*EVENT_COMPONENT_H*/