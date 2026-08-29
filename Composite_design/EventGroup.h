#ifndef EVENT_GROUP_H
#define EVENT_GROUP_H

#include "EventComponent.h";

class EventGroup : public EventComponent, public Subject, public Observer {
private:
    std::vector<EventComponent*> children;
    std::vector<Observer*> observers;
    Notice currentNotice;


public:


    explicit EventGroup(const std::string& name)
    
    void add(EventComponent* component);
    void remove(EventComponent* component);

    void open() override;
    void close() override;
    void reportStatus() const override;
    int getCapacity() const override;

    void attach(Observer* observer) override;
    void detach(Observer* observer) override;
    void notify() override;
    void update(const Notice& notice) override;
    void issueNotice(const Notice& notice);

     ~EventGroup() override;


};




#endif /*EVENT_GROUP_H*/