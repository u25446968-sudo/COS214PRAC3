#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Subject{
    private:
       std::vector<Observer*> observerList;
    protected:
       void notify(const Notify& notice)const; //outside shouldn't be able to call notify()
    public:
       virtual ~Subject();
       void attach(Observer*);
       void detach(Observer*); 
};

#endif